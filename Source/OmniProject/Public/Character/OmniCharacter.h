#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OmniCharacter.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

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

	//=========
	//Functions
	//=========

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

};
