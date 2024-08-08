#include "Character/OmniAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Character/OmniCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "HeaderFiles/DebugMacros.h"

void UOmniAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OmniCharacter = Cast<AOmniCharacter>(TryGetPawnOwner());
	if (OmniCharacter)
	{
		OmniCharacterMovement = OmniCharacter->GetCharacterMovement();
	}
}

void UOmniAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OmniCharacter)
	{
		CharacterWieldState = OmniCharacter->GetCharacterWieldState();
	}
	if (OmniCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(OmniCharacterMovement->Velocity);
		Direction = UKismetAnimationLibrary::CalculateDirection(OmniCharacterMovement->Velocity, OmniCharacter->GetActorRotation());
	}
}

