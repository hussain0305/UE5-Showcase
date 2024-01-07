#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OmniGlobal.h"
#include "Player/OmniInventory.h"
#include "Weapons/OmniWeapon.h"
#include "OmniCharacter.generated.h"

class UAnimMontage;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UAttributeSet;
class UAbilitySystemComponent;
class UOmniInventory;
class AOmniItem;
class AOmniWeapon;

UCLASS()
class OMNIPROJECT_API AOmniCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

//===========
//Constructor
//===========
	AOmniCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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
		UInputAction* InputAction_Sheath;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InputAction_Attack_PrimaryAction;

	//----------------
	// Ability System
	//----------------
	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
		TObjectPtr<UAttributeSet> AttributeSet;

	//-------------------
	// Animation Montages
	//-------------------
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* AttackMontage;

//==================================
//Setters, Getters, Inline Functions
//==================================

	//--------------------------------------------------------------------------------------
	// Wielding Helpers - Weapon currently being wielded by the character, NOT being carried
	//--------------------------------------------------------------------------------------
	UFUNCTION(BlueprintPure)
		bool BP_GetCharacterIsWieldingWeapon() const { return GetCharacterIsWieldingWeapon();}

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
	FORCEINLINE bool GetCanAttackPrimaryAction() const { return CharacterActionState == ECharacterActionState::Idle && CharacterWieldState != ECharacterWieldState::Unequipped;}
	
	//-------
	// Others
	//-------
	FORCEINLINE bool GetCharacterIsOverlappingWeapon() const { return OverlappingWeapon != nullptr;}

//=========
//Functions
//=========

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
		void SetOverlappingItemBegin(AOmniItem* OverlappedItem);
	UFUNCTION()
		void SetOverlappingItemEnd(AOmniItem* OverlappedItem);
	UFUNCTION()
		void SetOverlappingWeaponBegin(AOmniWeapon* OverlappedWeapon);
	UFUNCTION()
		void SetOverlappingWeaponEnd(AOmniWeapon* OverlappedWeapon);
	UFUNCTION(BlueprintCallable)
		void AttackEnded();
		
protected:

	virtual void BeginPlay() override;

	//-------------------------
	// Input Handling Functions
	//-------------------------
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	UFUNCTION()
		void TryPickupWeapon();
	UFUNCTION()
		void EquipWeapon(AOmniWeapon* OverlappedWeapon);
	UFUNCTION()
		void DropWeapon(AOmniWeapon* WeaponToDrop);
	UFUNCTION()
		void TrySheathOrUnsheath();
	UFUNCTION()
		void TryAttack_PrimaryAction();

private:

//======================================
//Private Pointers, Variables and Fields
//======================================

	UPROPERTY(VisibleAnywhere)
		AOmniItem* OverlappingItem = nullptr;
	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* OverlappingWeapon = nullptr;
	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* EquippedWeapon = nullptr;
	UPROPERTY(VisibleAnywhere)
		ECharacterWieldState CharacterWieldState = ECharacterWieldState::Unequipped;
	UPROPERTY(VisibleAnywhere)
		ECharacterActionState CharacterActionState = ECharacterActionState::Idle;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UOmniInventory> Inventory;
};
