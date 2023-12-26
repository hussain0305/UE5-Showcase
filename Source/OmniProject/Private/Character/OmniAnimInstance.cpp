#include "Character/OmniAnimInstance.h"
#include "Character/OmniCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	}
}

