#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OmniAnimInstance.generated.h"

class AOmniCharacter;

UCLASS()
class OMNIPROJECT_API UOmniAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	//==============================
	//Pointers, Variables and Fields
	//==============================

	UPROPERTY(BlueprintReadOnly)
		AOmniCharacter* OmniCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		class UCharacterMovementComponent* OmniCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float GroundSpeed;

	//=========
	//Functions
	//=========

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

};
