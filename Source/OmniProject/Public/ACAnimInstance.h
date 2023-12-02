#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ACAnimInstance.generated.h"

class AACCharacter;

UCLASS()
class OMNIPROJECT_API UACAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	//==============================
	//Pointers, Variables and Fields
	//==============================

	UPROPERTY(BlueprintReadOnly)
		AACCharacter* ACCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		class UCharacterMovementComponent* ACCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float GroundSpeed;

	//=========
	//Functions
	//=========

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

};
