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
	
	void StartThrowTrajectory(const FVector Origin, const FVector Target, const FVector FinalRotation, const TArray<AActor*> IgnoreActors);
	void ThrowTrajectory();
	FVector ComputeAxeThrowBezier(float t, FVector P0, FVector P1, FVector P2);
	bool CheckForCollision();
	FRotator CalculateLodgedRotation(const FVector& HitNormal) const;
	
	UPROPERTY(EditDefaultsOnly)
	float CurveStrength = 200.0f;

	UPROPERTY(EditDefaultsOnly)
	float ThrowSpeed = 3000.0f;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = -1800.0f;

	UPROPERTY(EditDefaultsOnly)
	FVector Gravity = FVector(0, 0, -490.0f);

private:

	float Distance;
	float TotalTime;
	float ElapsedTime;

	FVector TrajectoryStart;
	FVector TrajectoryEnd;
	FVector Direction;
	FVector RightVector;
	FVector ControlPoint;
	FVector HitNormal;
	
	FTimerHandle AxeThrowTimerHandle;
	TArray<AActor*> IgnoredActors;
};
