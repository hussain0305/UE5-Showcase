// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/OmniWeapon.h"
#include "OmniWeapon_ThrowingAxe.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API AOmniWeapon_ThrowingAxe : public AOmniWeapon
{
	GENERATED_BODY()

public:
	
	void StartThrowTrajectory(const FVector Origin, const FVector Target);
	void ThrowTrajectory();
	FVector ComputeAxeThrowBezier(float t, FVector P0, FVector P1, FVector P2);

	UPROPERTY(EditDefaultsOnly)
	float CurveStrength = 200.0f;

	UPROPERTY(EditDefaultsOnly)
	float ThrowSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 360.0f;

private:

	FVector TrajectoryStart;
	FVector TrajectoryEnd;
	FVector Direction;
	FVector RightVector;
	FVector ControlPoint;

	float Distance;
	float TotalTime;
	float ElapsedTime;

	FTimerHandle AxeThrowTimerHandle;
};
