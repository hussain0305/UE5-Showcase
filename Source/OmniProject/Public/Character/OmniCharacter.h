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

//==============================
//Pointers, Variables and Fields
//==============================

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

	//----------------
	// Ability System
	//----------------

	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
		TObjectPtr<UAttributeSet> AttributeSet;
	
//==================================
//Setters, Getters, Inline Functions
//==================================

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState;}

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

	UFUNCTION()
		void TryEquipOrUnequipWeapon();

	UFUNCTION()
		void TryEquipWeapon(AOmniWeapon* OverlappedWeapon);

protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

private:

	UPROPERTY(VisibleAnywhere)
		AOmniItem* OverlappingItem = nullptr;
	
	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* OverlappingWeapon = nullptr;

	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* EquippedWeapon = nullptr;

	UPROPERTY(VisibleAnywhere)
		ECharacterState CharacterState = ECharacterState::Unequipped;
};
