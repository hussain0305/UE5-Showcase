#include "ACAnimInstance.h"
#include "ACCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UACAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ACCharacter = Cast<AACCharacter>(TryGetPawnOwner());
	if (ACCharacter)
	{
		ACCharacterMovement = ACCharacter->GetCharacterMovement();
	}
}

void UACAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (ACCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(ACCharacterMovement->Velocity);
	}
}
