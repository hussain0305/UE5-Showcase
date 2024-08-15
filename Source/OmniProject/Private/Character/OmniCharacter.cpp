// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OmniCharacter.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h"
#include "Weapons/OmniWeapon.h"
#include "Items/OmniItem.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Player/OmniController.h"
#include "Animation/AnimMontage.h"
#include "HeaderFiles/DebugMacros.h"
#include "HeaderFiles/OmniGlobal.h"
#include "Components/CapsuleComponent.h"
#include "GameplayAbilitySystem/OmniAbilitySystemComponent.h"
#include "GameplayAbilitySystem/OmniAttributeSet.h"
#include "Player/OmniPlayerState.h"
#include "UI/OmniHUD.h"
#include <string>
#include "Camera/OmniCameraManager.h"
#include "Character/OmniAnimInstance.h"

AOmniCharacter::AOmniCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionProfileName(CHARACTER_COLLISION_PROFILE);
	GetCapsuleComponent()->SetCollisionProfileName(CHARACTER_COLLISION_PROFILE);
	
	//Setup Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	//Setup Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->bUsePawnControlRotation = true;

	CameraManager = CreateDefaultSubobject<UOmniCameraManager>(FName("Camera Manager"));
	CameraManager->SetupCameraManager(Camera, this);
	
	//Controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	// GetCharacterMovement()->bOrientRotationToMovement;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0f, 0);

	//Initialize Supporting stuff
	Inventory = CreateDefaultSubobject<UOmniInventory>(FName("Inventory"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AOmniCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info for the server
	InitAbilityActorInfo();
}

void AOmniCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	//Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AOmniCharacter::InitAbilityActorInfo()
{
	AOmniPlayerState* OmniPlayerState = GetPlayerState<AOmniPlayerState>();
	check(OmniPlayerState);
	OmniPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(OmniPlayerState, this);
	Cast<UOmniAbilitySystemComponent>(OmniPlayerState->GetAbilitySystemComponent())->Init();
	AbilitySystemComponent = Cast<UOmniAbilitySystemComponent>(OmniPlayerState->GetAbilitySystemComponent());
	AttributeSet = Cast<UOmniAttributeSet>(OmniPlayerState->GetAttributeSet());

	InitHUD();
}

void AOmniCharacter::InitHUD() const
{
	if (AOmniController* OmniController = Cast<AOmniController>(GetController()))
	{
		if (AOmniHUD* OmniHUD = Cast<AOmniHUD>(OmniController->GetHUD()))
		{
			FOmniWidgetControllerParams WidgetControllerParams(OmniController, GetPlayerState<AOmniPlayerState>(), AttributeSet, AbilitySystemComponent);
			OmniHUD->InitializeHUD(WidgetControllerParams);
		}
	}
}

UAbilitySystemComponent* AOmniCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AOmniCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AOmniCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (const AOmniController* PlayerController = Cast<AOmniController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AOmniCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputAction_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(InputAction_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(InputAction_Move, ETriggerEvent::Triggered, this, &AOmniCharacter::Move);
		EnhancedInputComponent->BindAction(InputAction_Look, ETriggerEvent::Triggered, this, &AOmniCharacter::Look);
		EnhancedInputComponent->BindAction(InputAction_Equip, ETriggerEvent::Triggered, this, &AOmniCharacter::HandleWeapon);
		EnhancedInputComponent->BindAction(InputAction_OneHandedToggleSheath, ETriggerEvent::Triggered, this, &AOmniCharacter::OneHandedWeaponToggleSheath);
		EnhancedInputComponent->BindAction(InputAction_TwoHandedToggleSheath, ETriggerEvent::Triggered, this, &AOmniCharacter::TwoHandedWeaponToggleSheath);
		EnhancedInputComponent->BindAction(InputAction_Attack_PrimaryAction, ETriggerEvent::Triggered, this, &AOmniCharacter::PrimaryAttackInput);
		EnhancedInputComponent->BindAction(InputAction_Attack_SecondaryAction, ETriggerEvent::Started, this, &AOmniCharacter::AimInput);
		EnhancedInputComponent->BindAction(InputAction_Attack_SecondaryAction, ETriggerEvent::Completed, this, &AOmniCharacter::StopAimInput);
	}
}

void AOmniCharacter::SetOverlappingItemBegin(AOmniItem* OverlappedItem)
{
	//Show prompt to press Equip button

	OverlappingItem = OverlappedItem;
}

void AOmniCharacter::SetOverlappingItemEnd(AOmniItem* OverlappedItem)
{
	//Remove prompt to press Equip button

	OverlappingItem = nullptr;
}

void AOmniCharacter::SetOverlappingWeaponBegin(AOmniWeapon* OverlappedWeapon)
{
	//Show prompt to press Equip button
	if (OverlappedWeapon->GetItemState() == EItemState::Pickup)
	{
		OverlappingWeapon = OverlappedWeapon;
	}
}

void AOmniCharacter::SetOverlappingWeaponEnd(const AOmniWeapon* OverlappedWeapon)
{
	//Remove prompt to press Equip button

	if (OverlappedWeapon == OverlappingWeapon)
	{
		OverlappingWeapon = nullptr;
	}
}

void AOmniCharacter::HandleWeapon()
{
	//Is wielding a weapon which is NOT the same type as overlapping weapon - holster the current weapon, pickup overlapping
	//Is wielding or has a weapon stowed away which is the same type as overlapping weapon - drop current weapon, pickup new
	const TObjectPtr<AOmniWeapon> WeaponToPickup = OverlappingWeapon;
	
	if (GetCharacterIsOverlappingWeapon())
	{
		if (GetInventory()->GetHasWeaponOfTypeInInventory(OverlappingWeapon->WeaponType))
		{
			const TObjectPtr<AOmniWeapon> WeaponToDrop = GetInventory()->GetWeaponOfTypeInInventory(OverlappingWeapon->WeaponType);
			if(WeaponToDrop != nullptr)
			{
				PRINT_DEBUG_MESSAGE_WITH_PARAMETER(5.f, FColor::Emerald, FString("Droping "), WeaponToDrop->GetName());
				DropWeapon(WeaponToDrop);
			}
		}
		if(GetInventory()->GetIsWieldingWeaponOfDifferentType(OverlappingWeapon->WeaponType))
		{
			PRINT_DEBUG_MESSAGE_WITH_PARAMETER(5.f, FColor::Emerald, FString("Sheathing "), GetInventory()->GetWieldedWeapon()->GetName());
			SheathWeapon();
		}
		EquipWeapon(WeaponToPickup);
		
		//Placed OverlappingWeapon = nullptr because later, I might add a mechanic where weapons are acquired from other sources rather than overlapping,
		//so I might not want to set it to nullptr in every case
		OverlappingWeapon = nullptr;
	}
}

void AOmniCharacter::EquipWeapon(AOmniWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr)
	{
		return;
	}
	PRINT_DEBUG_MESSAGE_WITH_PARAMETER(5.f, FColor::Emerald, FString("Equipping "), WeaponToEquip->GetName());

	WeaponToEquip->SetItemState(EItemState::Equipped);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponToEquip->StaticMesh->AttachToComponent(GetMesh(), AttachmentRules, GetWeaponWieldingSocket(WeaponToEquip->WeaponType));
	WeaponToEquip->ScabbardMesh->AttachToComponent(GetMesh(), AttachmentRules, GetWeaponScabbardSocket(WeaponToEquip->WeaponType));
	WeaponToEquip->SetWielder(this);

	GetInventory()->SetWeaponInInventory(WeaponToEquip);
	GetInventory()->SetWieldedWeapon(WeaponToEquip);
	SetCharacterWieldState(WeaponToEquip);
	SetCharacterActionState(ECharacterActionState::Idle);
}

void AOmniCharacter::EquipWeaponOfTypeFromInventory(EWeaponType WeaponType)
{
	AOmniWeapon* WeaponToEquip = GetInventory()->GetWeaponOfTypeInInventory(WeaponType);
	if (WeaponToEquip != nullptr)
	{
		EquipWeapon(WeaponToEquip);
	}
}

void AOmniCharacter::SheathWeapon()
{
	AOmniWeapon* WeaponToSheath = GetInventory()->GetWieldedWeapon();
	if (WeaponToSheath == nullptr)
	{
		return;
	}

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	//Detach Scabbard from body
	const FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, false);
	WeaponToSheath->ScabbardMesh->DetachFromComponent((DetachmentRules));
	//Attach Scabbard back to weapon
	WeaponToSheath->ScabbardMesh->AttachToComponent(WeaponToSheath->StaticMesh, AttachmentRules);
	//Attach to character body
	WeaponToSheath->AttachToComponent(GetMesh(), AttachmentRules, GetWeaponScabbardSocket(WeaponToSheath->WeaponType));
	WeaponToSheath->SetItemState(EItemState::Sheathed);
	
	GetInventory()->SetWieldedWeapon(nullptr);
	SetCharacterWieldState(nullptr);

	SetCharacterActionState(ECharacterActionState::Idle);
}

void AOmniCharacter::DropWeapon(AOmniWeapon* WeaponToDrop)
{
	if (WeaponToDrop == nullptr)
	{
		return;
	}

	//Detach Scabbard from body
	const FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, false);
	WeaponToDrop->ScabbardMesh->DetachFromComponent((DetachmentRules));
	//Attach Scabbard back to weapon
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponToDrop->ScabbardMesh->AttachToComponent(WeaponToDrop->StaticMesh, AttachmentRules);
	//Drop Weapon, reset it as a pickup
	WeaponToDrop->StaticMesh->DetachFromComponent(DetachmentRules);
	WeaponToDrop->SetItemState(EItemState::Pickup);
	WeaponToDrop->SetWielder(nullptr);
	const EWeaponType DroppedWeaponType = WeaponToDrop->WeaponType;

	GetInventory()->SetWeaponInInventory(DroppedWeaponType, nullptr);
	if (GetInventory()->GetWieldedWeaponDropped(WeaponToDrop))
	{
		GetInventory()->SetWieldedWeapon(nullptr);
	}
	SetCharacterWieldState(nullptr);
}

void AOmniCharacter::OneHandedWeaponToggleSheath()
{
	if(!GetInventory()->GetHasWeaponOfTypeInInventory(EWeaponType::OneHandedWeapon))
	{
		PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString("No weapon found in inventory"));
		return;
	}

	ToggleSheath(EWeaponType::OneHandedWeapon);
}

void AOmniCharacter::TwoHandedWeaponToggleSheath()
{
	if(!GetInventory()->GetHasWeaponOfTypeInInventory(EWeaponType::TwoHandedWeapon))
	{
		return;
	}
	
	ToggleSheath(EWeaponType::TwoHandedWeapon);
}

void AOmniCharacter::ToggleSheath(EWeaponType WeaponType)
{
	if (GetCharacterIsWieldingWeapon())
	{
		if (GetInventory()->GetIsWieldingWeaponOfDifferentType(WeaponType))
		{
			SheathWeapon();
			PlayWeaponUnsheathAnimation(GetInventory()->GetWeaponOfTypeInInventory(WeaponType));
		}
		else
		{
			PlayWeaponSheathAnimation(GetInventory()->GetWieldedWeapon());
		}
	}
	else
	{
		PlayWeaponUnsheathAnimation(GetInventory()->GetWeaponOfTypeInInventory(WeaponType));
	}
}

void AOmniCharacter::SetCharacterWieldState(const TObjectPtr<AOmniWeapon> CurrentlyWieldedWeapon)
{
	if (CurrentlyWieldedWeapon == nullptr)
	{
		CharacterWieldState = ECharacterWieldState::Unequipped;
		return;
	}
	switch(CurrentlyWieldedWeapon->WeaponType)
	{
		case EWeaponType::OneHandedWeapon:
			CharacterWieldState = ECharacterWieldState::OneHandedWeapon;
			break;
		case EWeaponType::TwoHandedWeapon:
			CharacterWieldState=ECharacterWieldState::TwoHandedWeapon;
			break;
	}
}

UOmniAnimInstance* AOmniCharacter::GetOmniAnimInstance()
{
	if (OmniAnimInstance != nullptr)
	{
		return OmniAnimInstance;
	}
	if (UAnimInstance* tAnimInstance = GetMesh()->GetAnimInstance())
	{
		OmniAnimInstance = Cast<UOmniAnimInstance>(tAnimInstance);
		return OmniAnimInstance;
	}
	return nullptr;
}

//TODO: Make this Function better. Unsheathing should not require a reference to the weapon, just unsheath the currently equipped one
void AOmniCharacter::PlayWeaponSheathAnimation(AOmniWeapon* WeaponToSheath)
{
	if (WeaponToSheath == nullptr)
	{
		return;
	}
	if (!GetCanSheathWeapon())
	{
		return;
	}
	if (!GetInventory() || !GetInventory()->GetWieldedWeapon())
	{
		return;
	}

	FOmniWeaponTable WeaponConfig = GetInventory()->GetWieldedWeapon()->GetWeaponConfig();
	const FAnimationDetails SheathMontageDetails = WeaponConfig.SheathMontage;
	UAnimMontage* SheathMontage = SheathMontageDetails.AnimationMontage;
	GetOmniAnimInstance()->AnimatedBodyPart =  SheathMontageDetails.BodyPart;
	if (OmniAnimInstance && SheathMontage)
	{
		OmniAnimInstance->Montage_Play(SheathMontage);
		SetCharacterActionState(ECharacterActionState::OtherAction);
	}
}

void AOmniCharacter::PlayWeaponUnsheathAnimation(AOmniWeapon* WeaponToUnsheath)
{
	if (WeaponToUnsheath == nullptr)
	{
		return;
	}
	if (!GetCanUnsheathWeapon())
	{
		return;
	}
	if (!GetInventory() || GetInventory()->GetWieldedWeapon())
	{
		return;
	}

	FOmniWeaponTable WeaponConfig = WeaponToUnsheath->GetWeaponConfig();
	const FAnimationDetails UnsheathMontageDetails = WeaponConfig.UnsheathMontage;
	UAnimMontage* UnsheathMontage = UnsheathMontageDetails.AnimationMontage;
	GetOmniAnimInstance()->AnimatedBodyPart =  UnsheathMontageDetails.BodyPart;
	if (OmniAnimInstance && UnsheathMontage)
	{
		OmniAnimInstance->Montage_Play(UnsheathMontage);
		SetCharacterActionState(ECharacterActionState::OtherAction);
	}
}

void AOmniCharacter::PrimaryAttackInput()
{
	if (!GetCharacterIsWieldingWeapon())
	{
		return;
	}
	if (GetCanPerformPrimaryWeaponAction())
	{
		PrimaryAttackAction();
	}
	else if(GetCanPerformSecondaryWeaponAction())
	{
		SecondaryAttackAction();
	}
}

void AOmniCharacter::AimInput()
{
	if (!GetCharacterIsWieldingWeapon())
	{
		return;
	}
	if (GetCanAim())
	{
		StartAim();
	}
}

void AOmniCharacter::StopAimInput()
{
	PRINT_DEBUG_MESSAGE(5.f, FColor::Purple, FString("Released"));
	OnIsAimingChanged.Broadcast(false);
	if(GetIsAiming())
	{
		StopAim();
	}
}

void AOmniCharacter::PrimaryAttackAction()
{
	const TObjectPtr<AOmniWeapon> WieldedWeapon = GetInventory()->GetWieldedWeapon();

	if (WieldedWeapon == nullptr)
	{
		return;
	}

	FOmniWeaponTable WeaponConfig = WieldedWeapon->GetWeaponConfig();
	const FAnimationDetails AttackMontageDetails = WeaponConfig.PrimaryAttack;
	UAnimMontage* AttackMontage = AttackMontageDetails.AnimationMontage;
	GetOmniAnimInstance()->AnimatedBodyPart =  AttackMontageDetails.BodyPart;

	if (OmniAnimInstance && AttackMontage)
	{
		const int8 SectionToPlay = WieldedWeapon->GetMontageSectionToPlay(GetLocomotionState());
		std::string SectionName = "Attack";
		SectionName += std::to_string(SectionToPlay);
		OmniAnimInstance->Montage_Play(AttackMontage);
		OmniAnimInstance->Montage_JumpToSection(FName(SectionName.c_str()), AttackMontage);
		PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString(SectionName.c_str()));
		SetCharacterActionState(ECharacterActionState::Attacking_PrimaryAction);
	}
}

void AOmniCharacter::StartAim()
{
	const TObjectPtr<AOmniWeapon> WieldedWeapon = GetInventory()->GetWieldedWeapon();
	if (WieldedWeapon == nullptr)
	{
		return;
	}
	FOmniWeaponTable WeaponConfig = WieldedWeapon->GetWeaponConfig();
	if (WeaponConfig.SecondaryAttackType != ESecondaryAttack::Aimed)
	{
		return;
	}
	const FAnimationDetails SecondaryAttackMontageDetails = WeaponConfig.SecondaryAttack;
	GetOmniAnimInstance()->AnimatedBodyPart =  SecondaryAttackMontageDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = SecondaryAttackMontageDetails.AnimationMontage;
	
	if (OmniAnimInstance && SecondaryActionMontage)
	{
		OnIsAimingChanged.Broadcast(true);
		SecondaryActionMontage->bLoop = true;
		OmniAnimInstance->Montage_Play(SecondaryActionMontage);
		OmniAnimInstance->Montage_JumpToSection(WeaponConfig.MontageSectionName_Aim, SecondaryActionMontage);
		OmniAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 1.f);
		SetCharacterActionState(ECharacterActionState::AimStart_SecondaryAction);
	}
}

void AOmniCharacter::AimStay()
{
	const TObjectPtr<AOmniWeapon> WieldedWeapon = GetInventory()->GetWieldedWeapon();
	FOmniWeaponTable WeaponConfig = WieldedWeapon->GetWeaponConfig();
	const FAnimationDetails SecondaryAttackMontageDetails = WeaponConfig.SecondaryAttack;
	GetOmniAnimInstance()->AnimatedBodyPart =  SecondaryAttackMontageDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = SecondaryAttackMontageDetails.AnimationMontage;
	
	if (OmniAnimInstance && SecondaryActionMontage)
	{
		SecondaryActionMontage->bLoop = true;
		OmniAnimInstance->Montage_Play(SecondaryActionMontage);
		OmniAnimInstance->Montage_JumpToSection(WeaponConfig.MontageSectionName_AimStay, SecondaryActionMontage);
		OmniAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 1.f);
		SetCharacterActionState(ECharacterActionState::AimDone_SecondaryAction);
	}
}

void AOmniCharacter::PerformSecondaryWeaponAction()
{
	if (GetInventory()->GetWieldedWeapon())
	{
		GetInventory()->GetWieldedWeapon()->PerformSecondaryAction(this);
	}
}

void AOmniCharacter::StopAim()
{
	OnIsAimingChanged.Broadcast(false);
	const TObjectPtr<AOmniWeapon> WieldedWeapon = GetInventory()->GetWieldedWeapon();
	FOmniWeaponTable WeaponConfig = WieldedWeapon->GetWeaponConfig();
	const FAnimationDetails SecondaryAttackMontageDetails = WeaponConfig.SecondaryAttack;
	GetOmniAnimInstance()->AnimatedBodyPart =  SecondaryAttackMontageDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = SecondaryAttackMontageDetails.AnimationMontage;
	if (OmniAnimInstance && SecondaryActionMontage)
	{
		OmniAnimInstance->Montage_Play(SecondaryActionMontage);
		OmniAnimInstance->Montage_JumpToSection(WeaponConfig.MontageSectionName_Aim, SecondaryActionMontage);
		OmniAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, -1);
		SetCharacterActionState(ECharacterActionState::Idle);
	}
}

void AOmniCharacter::SecondaryAttackAction()
{
	if (!GetIsAiming())
	{
		return;
	}
	const TObjectPtr<AOmniWeapon> WieldedWeapon = GetInventory()->GetWieldedWeapon();
	FOmniWeaponTable WeaponConfig = WieldedWeapon->GetWeaponConfig();
	const FAnimationDetails SecondaryAttackMontageDetails = WeaponConfig.SecondaryAttack;
	GetOmniAnimInstance()->AnimatedBodyPart =  SecondaryAttackMontageDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = SecondaryAttackMontageDetails.AnimationMontage;
	if (OmniAnimInstance && SecondaryActionMontage)
	{
		SecondaryActionMontage->bLoop = false;
		OmniAnimInstance->Montage_Play(SecondaryActionMontage);
		OmniAnimInstance->Montage_JumpToSection(WeaponConfig.MontageSectionName_AimAttack, SecondaryActionMontage);
		OmniAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 5.f);
		SetCharacterActionState(ECharacterActionState::Attacking_SecondaryAction);
	}
}

void AOmniCharacter::AttackEnded()
{
	SetCharacterActionState(ECharacterActionState::Idle);
}

void AOmniCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOmniCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

ECharacterLocomotionState AOmniCharacter::GetLocomotionState()
{
	if (GetMovementComponent()->IsFalling())
	{
		return ECharacterLocomotionState::Falling;
	}
	if (GetMovementComponent()->Velocity.Length() > 0)
	{
		return ECharacterLocomotionState::Running;
	}

	return ECharacterLocomotionState::Stationary;
}