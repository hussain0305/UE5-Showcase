#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OmniGlobal.h"
#include "OmniCharacter.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UAttributeSet;
class UAbilitySystemComponent;
class AOmniItem;
class AOmniWeapon;
class UAnimMontage;

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

	FORCEINLINE ECharacterWieldState GetCharacterWieldState() const { return CharacterWieldState;}
	FORCEINLINE ECharacterActionState GetCharacterActionState() const { return CharacterActionState;}
	FORCEINLINE void SetCharacterActionState(const ECharacterActionState NewActionState) { CharacterActionState = NewActionState;}
	FORCEINLINE bool GetCanAttackPrimaryAction() const { return CharacterActionState == ECharacterActionState::Idle && CharacterWieldState != ECharacterWieldState::Unequipped;}

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
		void TryEquipOrUnequipWeapon();
	UFUNCTION()
		void TryEquipWeapon(AOmniWeapon* OverlappedWeapon);
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
};
