// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OmniCharacter.h"
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
#include "DebugMacros.h"
#include "Components/SphereComponent.h"

AOmniCharacter::AOmniCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Setup Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;

	//Setup Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->bUsePawnControlRotation = true;

	//Controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0f, 0);

	//Initialize Supporting stuff
	Inventory = CreateDefaultSubobject<UOmniInventory>(FName("Inventory"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
		EnhancedInputComponent->BindAction(InputAction_Attack_PrimaryAction, ETriggerEvent::Triggered, this, &AOmniCharacter::TryAttack_PrimaryAction);
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
				DropWeapon(WeaponToDrop);
			}
		}
		else if(GetInventory()->GetIsWieldingWeaponOfDifferentType(OverlappingWeapon->WeaponType))
		{
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
	PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString("Equipping Weapon"));

	WeaponToEquip->SetItemState(EItemState::Equipped);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponToEquip->StaticMesh->AttachToComponent(GetMesh(), AttachmentRules, GetWeaponWieldingSocket(WeaponToEquip->WeaponType));
	WeaponToEquip->ScabbardMesh->AttachToComponent(GetMesh(), AttachmentRules, GetWeaponScabbardSocket(WeaponToEquip->WeaponType));
	
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
	PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString("Dropping Weapon"));

	//Detach Scabbard from body
	const FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, false);
	WeaponToDrop->ScabbardMesh->DetachFromComponent((DetachmentRules));
	//Attach Scabbard back to weapon
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponToDrop->ScabbardMesh->AttachToComponent(WeaponToDrop->StaticMesh, AttachmentRules);
	//Drop Weapon, reset it as a pickup
	WeaponToDrop->StaticMesh->DetachFromComponent(DetachmentRules);
	WeaponToDrop->SetItemState(EItemState::Pickup);
	const EWeaponType DroppedWeaponType = WeaponToDrop->WeaponType;

	GetInventory()->SetWeaponInInventory(DroppedWeaponType, nullptr);
	GetInventory()->SetWieldedWeapon(nullptr);
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
	PRINT_DEBUG_MESSAGE(5.f, FColor::Green, FString("Toggle Sheath called"));
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

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* SheathMontage = GetInventory()->GetWieldedWeapon()->SheathMontage;
	if (AnimInstance && SheathMontage)
	{
		AnimInstance->Montage_Play(SheathMontage);
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

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* UnsheathMontage = WeaponToUnsheath->UnsheathMontage;
	if (AnimInstance && UnsheathMontage)
	{
		AnimInstance->Montage_Play(UnsheathMontage);
		SetCharacterActionState(ECharacterActionState::OtherAction);
	}
}

void AOmniCharacter::TryAttack_PrimaryAction()
{
	if (!GetCanAttackPrimaryAction())
	{
		return;
	}
	if (!GetInventory() || !GetInventory()->GetWieldedWeapon())
	{
		return;
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* AttackMontage = GetInventory()->GetWieldedWeapon()->AttackMontage;
	if (AnimInstance && AttackMontage)
	{
		const int32 SectionToPlay = FMath::RandRange(1,4);
		std::string SectionName = "Attack";
		SectionName += std::to_string(SectionToPlay);
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(FName(SectionName.c_str()), AttackMontage);
		PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString(SectionName.c_str()));
		SetCharacterActionState(ECharacterActionState::Attacking_PrimaryAction);
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
