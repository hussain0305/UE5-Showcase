// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OmniWeapon_ThrowingAxe.h"
#include "HeaderFiles/DebugMacros.h"

void AOmniWeapon_ThrowingAxe::StartThrowTrajectory(const FVector Origin, const FVector Target)
{
	PRINT_DEBUG_MESSAGE(5.f, FColor::Black, FString("StartThrowTrajectory"));
	TrajectoryStart = Origin;
	TrajectoryEnd = Target;
	Direction = (Target - Origin).GetSafeNormal();
	RightVector = FVector::CrossProduct(Direction, FVector::UpVector).GetSafeNormal();
	ControlPoint = Origin + Direction * 0.5f * FVector::Dist(Origin, Target) - RightVector * CurveStrength;

	Distance = FVector::Dist(Origin, Target);
	TotalTime = Distance / ThrowSpeed;

	ElapsedTime = 0.0f;

	GetWorldTimerManager().SetTimer(AxeThrowTimerHandle, this, &AOmniWeapon_ThrowingAxe::ThrowTrajectory, GetWorld()->GetDeltaSeconds(), true);
}

void AOmniWeapon_ThrowingAxe::ThrowTrajectory()
{
	ElapsedTime += GetWorld()->GetDeltaSeconds();

	if (ElapsedTime >= TotalTime)
	{
		GetWorldTimerManager().ClearTimer(AxeThrowTimerHandle);
		SetActorLocation(TrajectoryEnd);
		SetActorRotation(TrajectoryEnd.Rotation());
		return;
	}

	float t = ElapsedTime / TotalTime;

	FVector NewPosition = ComputeAxeThrowBezier(t, TrajectoryStart, TrajectoryEnd, ControlPoint);

	float RotationAngle = RotationSpeed * GetWorld()->GetDeltaSeconds();
	FRotator NewRotation = FRotator(RotationAngle, 0, 0);
	AddActorLocalRotation(NewRotation);
	SetActorLocation(NewPosition);
}

FVector AOmniWeapon_ThrowingAxe::ComputeAxeThrowBezier(float t, FVector P0, FVector P1, FVector P2)
{
	FVector Position = FMath::Pow(1 - t, 2) * P0 +
					   2 * (1 - t) * t * P2 +
					   FMath::Pow(t, 2) * P1;

	return Position;
}
