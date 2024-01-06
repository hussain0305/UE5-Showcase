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

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0f, 0);

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
		EnhancedInputComponent->BindAction(InputAction_Equip, ETriggerEvent::Triggered, this, &AOmniCharacter::TryEquipOrUnequipWeapon);
		EnhancedInputComponent->BindAction(InputAction_Sheath, ETriggerEvent::Triggered, this, &AOmniCharacter::TryEquipOrUnequipWeapon);
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

	OverlappingWeapon = OverlappedWeapon;
}

void AOmniCharacter::SetOverlappingWeaponEnd(AOmniWeapon* OverlappedWeapon)
{
	//Remove prompt to press Equip button

	OverlappingWeapon = nullptr;
}

void AOmniCharacter::TryEquipOrUnequipWeapon()
{
	if (OverlappingWeapon == nullptr && EquippedWeapon == nullptr)
	{
		return;
	}
	
	if (GetCharacterIsWieldingWeapon())
	{
		UnequipWeapon();
		return;
	}

	if (GetCharacterIsOverlappingWeapon())
	{
		EquipWeapon(OverlappingWeapon);
		
		//Placed OverlappingWeapon = nullptr because later, I might add a mechanic where weapons are acquired from other sources rather than overlapping,
		//so I might not want to set it to nullptr in every case
		OverlappingWeapon = nullptr;
	}
}

void AOmniCharacter::EquipWeapon(AOmniWeapon* OverlappedWeapon)
{
	if (OverlappedWeapon == nullptr)
	{
		return;
	}
	
	PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString("Equipping Weapon"));

	OverlappedWeapon->SetItemState(EItemState::Equipped);

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	OverlappedWeapon->StaticMesh->AttachToComponent(GetMesh(), AttachmentRules, FName("RightHandSocket"));
	EquippedWeapon = OverlappedWeapon;

	CharacterWieldState = ECharacterWieldState::OneHandedWeapon;
}

void AOmniCharacter::UnequipWeapon()
{
	if (EquippedWeapon == nullptr)
	{
		return;
	}
	
	PRINT_DEBUG_MESSAGE(5.f, FColor::Red, FString("Unequipping Weapon"));
	
	const FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, false);
	EquippedWeapon->StaticMesh->DetachFromComponent(DetachmentRules);
	
	EquippedWeapon->SetItemState(EItemState::Pickup);
	EquippedWeapon = nullptr;

	CharacterWieldState = ECharacterWieldState::Unequipped;
}

void AOmniCharacter::TrySheathOrUnsheath()
{
	
}

void AOmniCharacter::TryAttack_PrimaryAction()
{
	if (!GetCanAttackPrimaryAction())
	{
		return;
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
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
