#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeaderFiles/OmniGlobal.h"
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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		AOmniCharacter* OmniCharacter;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		class UCharacterMovementComponent* OmniCharacterMovement;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		float Direction;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character State")
		ECharacterWieldState CharacterWieldState;

//=========
//Functions
//=========

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

};
