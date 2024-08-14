#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HeaderFiles/OmniGlobal.h"
#include "Player/OmniInventory.h"
#include "Weapons/OmniWeapon.h"
#include "OmniCharacter.generated.h"

class UOmniAnimInstance;
class UOmniAttributeSet;
class UOmniAbilitySystemComponent;
class UAnimMontage;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UOmniInventory;
class AOmniItem;
class AOmniWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIsAiming, bool, bIsAiming);

UCLASS()
class OMNIPROJECT_API AOmniCharacter : public ACharacter, public IAbilitySystemInterface//, public IDamageable
{
	GENERATED_BODY()

public:

//===========
//Constructor
//===========
	AOmniCharacter();

//=======================
//Callbacks and Delegates
//=======================
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintAssignable, Category = "HUD Delegate")
	FIsAiming OnIsAimingChanged;
	
//======
//Consts
//======
	const FName ONE_HANDED_WEAPON_SOCKET = "RightHandSocket";
	const FName TWO_HANDED_WEAPON_SOCKET = "RightHandSocket";
	const FName ONE_HANDED_SCABBARD_SOCKET = "OneHandedScabbard";
	const FName TWO_HANDED_SCABBARD_SOCKET = "TwoHandedScabbard";
	
//=====================================
//Public Pointers, Variables and Fields
//=====================================

	//--------
	// Camera
	//--------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Core Component")
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Core Component")
		UCameraComponent* Camera;

	//-------
	// Input
	//-------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Look;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Equip;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_OneHandedToggleSheath;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_TwoHandedToggleSheath;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Attack_PrimaryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Attack_SecondaryAction;

	//----------------
	// Ability System
	//----------------
	UPROPERTY()
		TObjectPtr<UOmniAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
		TObjectPtr<UOmniAttributeSet> AttributeSet;
	
//==================================
//Setters, Getters, Inline Functions
//==================================

	//--------------------------------------------------------------------------------------
	// Wielding Helpers - Weapon currently being wielded by the character, NOT being carried
	//--------------------------------------------------------------------------------------
	UFUNCTION(BlueprintPure)
		bool BP_GetCharacterIsWieldingWeapon() const { return GetCharacterIsWieldingWeapon();}
	UFUNCTION(BlueprintPure)
		AOmniWeapon* BP_GetWieldedWeapon() const { return GetInventory()->GetWieldedWeapon();}

	void SetCharacterWieldState(const TObjectPtr<AOmniWeapon> CurrentlyWieldedWeapon);
	FORCEINLINE ECharacterWieldState GetCharacterWieldState() const { return CharacterWieldState;}
	FORCEINLINE bool GetCharacterIsWieldingWeapon() const { return CharacterWieldState != ECharacterWieldState::Unequipped;}

	//---------------------------------------------------------------------
	// Inventory Helpers - Weapons currently being carried by the character
	//---------------------------------------------------------------------
	FORCEINLINE TObjectPtr<UOmniInventory> GetInventory() const {return Inventory;}

	//---------------
	// Action Helpers
	//---------------
	FORCEINLINE ECharacterActionState GetCharacterActionState() const { return CharacterActionState;}
	FORCEINLINE void SetCharacterActionState(const ECharacterActionState NewActionState) { CharacterActionState = NewActionState;}
	FORCEINLINE bool GetCanPerformPrimaryWeaponAction() const { return CharacterActionState == ECharacterActionState::Idle && CharacterWieldState != ECharacterWieldState::Unequipped && !GetIsInSecondaryAttackLoop();}
	FORCEINLINE bool GetCanAim() const { return CharacterActionState == ECharacterActionState::Idle && CharacterWieldState != ECharacterWieldState::Unequipped;}
	FORCEINLINE bool GetIsAiming() const { return CharacterActionState == ECharacterActionState::AimDone_SecondaryAction;}
	FORCEINLINE bool GetStartedAiming() const { return CharacterActionState == ECharacterActionState::AimStart_SecondaryAction;}
	FORCEINLINE bool GetCanPerformSecondaryWeaponAction() const { return CharacterActionState == ECharacterActionState::AimDone_SecondaryAction && CharacterWieldState != ECharacterWieldState::Unequipped;}
	FORCEINLINE bool GetCanSheathWeapon() const { return CharacterActionState == ECharacterActionState::Idle && CharacterWieldState != ECharacterWieldState::Unequipped;}
	FORCEINLINE bool GetCanUnsheathWeapon() const { return CharacterActionState == ECharacterActionState::Idle;}
	FORCEINLINE bool GetIsInSecondaryAttackLoop() const { return CharacterActionState == ECharacterActionState::AimStart_SecondaryAction || CharacterActionState == ECharacterActionState::AimDone_SecondaryAction;}
	
	//---------------
	// Ability System
	//---------------
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//-------
	// Others
	//-------
	FORCEINLINE bool GetCharacterIsOverlappingWeapon() const { return OverlappingWeapon != nullptr;}
	FORCEINLINE FName GetWeaponWieldingSocket(EWeaponType WeaponType) const { return WeaponType == EWeaponType::OneHandedWeapon ? ONE_HANDED_WEAPON_SOCKET : TWO_HANDED_WEAPON_SOCKET;}
	FORCEINLINE FName GetWeaponScabbardSocket(EWeaponType WeaponType) const { return WeaponType == EWeaponType::OneHandedWeapon ? ONE_HANDED_SCABBARD_SOCKET : TWO_HANDED_SCABBARD_SOCKET;}
	
//================
//Public Functions
//================

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//--------------------------------
	// Overlapping Weapons and Pickups
	//--------------------------------
	UFUNCTION()
		void SetOverlappingItemBegin(AOmniItem* OverlappedItem);
	UFUNCTION()
		void SetOverlappingItemEnd(AOmniItem* OverlappedItem);
	UFUNCTION()
		void SetOverlappingWeaponBegin(AOmniWeapon* OverlappedWeapon);
	UFUNCTION()
		void SetOverlappingWeaponEnd(const AOmniWeapon* OverlappedWeapon);

	//---------------
	// Weapon Actions
	//---------------
	UFUNCTION(BlueprintCallable)
		void AttackEnded();
	UFUNCTION()
		void PlayWeaponSheathAnimation(AOmniWeapon* WeaponToSheath);
	UFUNCTION(BlueprintCallable)
		void SheathWeapon();
	UFUNCTION()
		void PlayWeaponUnsheathAnimation(AOmniWeapon* WeaponToUnsheath);
	UFUNCTION(BlueprintCallable)
		void EquipWeapon(AOmniWeapon* WeaponToEquip);
	UFUNCTION(BlueprintCallable)
		void EquipWeaponOfTypeFromInventory(EWeaponType WeaponType);
	UFUNCTION()
		void DropWeapon(AOmniWeapon* WeaponToDrop);
	UFUNCTION()
		void AimStay();
	UFUNCTION()
		void PerformSecondaryWeaponAction();

	//-------
	// Others
	//-------

	UFUNCTION(BlueprintCallable)
		UOmniAnimInstance* GetOmniAnimInstance();

	UFUNCTION(BlueprintCallable)
		ECharacterLocomotionState GetLocomotionState();
protected:

	virtual void BeginPlay() override;

	//-------------------------
	// Input Handling Functions
	//-------------------------
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	UFUNCTION()
		void HandleWeapon();
	UFUNCTION()
		void OneHandedWeaponToggleSheath();
	UFUNCTION()
		void TwoHandedWeaponToggleSheath();
	UFUNCTION()
		void ToggleSheath(EWeaponType WeaponType);
	UFUNCTION()
		void PrimaryAttackInput();
	UFUNCTION()
		void PrimaryAttackAction();
	UFUNCTION()
		void AimInput();
	UFUNCTION()
		void StopAimInput();
	UFUNCTION()
		void StartAim();
	UFUNCTION()
		void StopAim();
	UFUNCTION()
		void SecondaryAttackAction();

	//-------------
	// Initializers
	//-------------
	void InitAbilityActorInfo();

private:

//======================================
//Private Pointers, Variables and Fields
//======================================

	UPROPERTY(VisibleAnywhere)
		AOmniItem* OverlappingItem = nullptr;
	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* OverlappingWeapon = nullptr;
	UPROPERTY(VisibleAnywhere)
		ECharacterWieldState CharacterWieldState = ECharacterWieldState::Unequipped;
	UPROPERTY(VisibleAnywhere)
		ECharacterActionState CharacterActionState = ECharacterActionState::Idle;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UOmniInventory> Inventory;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UOmniAnimInstance> OmniAnimInstance;

//=================
//Private Functions
//=================
	
	void InitHUD() const;
	
};
