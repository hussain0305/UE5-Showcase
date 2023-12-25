#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OmniCharacter.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class AOmniItem;
class AOmniWeapon;

UCLASS()
class OMNIPROJECT_API AOmniCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	//===========
	//Constructor
	//===========

	AOmniCharacter();

	//==============================
	//Pointers, Variables and Fields
	//==============================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Core Component")
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Core Component")
		UCameraComponent* Camera;

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

	//==================================
	//Setters, Getters, Inline Functions
	//==================================

	

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
		AOmniItem* OverlappingItem;
	
	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* OverlappingWeapon;

	UPROPERTY(VisibleAnywhere)
		AOmniWeapon* EquippedWeapon;
};
