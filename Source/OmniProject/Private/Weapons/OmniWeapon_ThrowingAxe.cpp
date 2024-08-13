// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OmniWeapon_ThrowingAxe.h"
#include "HeaderFiles/DebugMacros.h"
#include "Kismet/KismetSystemLibrary.h"

void AOmniWeapon_ThrowingAxe::StartThrowTrajectory(const FVector Origin, const FVector Target, const FVector FinalRotation, const TArray<AActor*> IgnoreActors)
{
	PRINT_DEBUG_MESSAGE(5.f, FColor::Black, FString("StartThrowTrajectory"));
	TrajectoryStart = Origin;
	TrajectoryEnd = Target;
	HitNormal = FinalRotation;
	IgnoredActors = IgnoreActors;
	
	Direction = (Target - Origin).GetSafeNormal();
	RightVector = FVector::CrossProduct(Direction, FVector::UpVector).GetSafeNormal();
	ControlPoint = Origin + Direction * 0.5f * FVector::Dist(Origin, Target) - RightVector * CurveStrength;

	Distance = FVector::Dist(Origin, Target);
	TotalTime = Distance / ThrowSpeed;

	ElapsedTime = 0.0f;
	DRAW_LINE(TrajectoryStart, TrajectoryEnd);
	DRAW_POINT(ControlPoint);
	GetWorldTimerManager().SetTimer(AxeThrowTimerHandle, this, &AOmniWeapon_ThrowingAxe::ThrowTrajectory, GetWorld()->GetDeltaSeconds(), true);
}

void AOmniWeapon_ThrowingAxe::ThrowTrajectory()
{
	ElapsedTime += GetWorld()->GetDeltaSeconds();

	if (ElapsedTime >= TotalTime)
	{
		GetWorldTimerManager().ClearTimer(AxeThrowTimerHandle);
		// SetActorLocation(TrajectoryEnd);
		return;
	}

	float t = ElapsedTime / TotalTime;

	FVector NewPosition = ComputeAxeThrowBezier(t, TrajectoryStart, TrajectoryEnd, ControlPoint);
	FVector GravityEffect = 0.5f * Gravity * FMath::Pow(ElapsedTime, 2); 
	NewPosition += GravityEffect;
	
	float RotationAngle = RotationSpeed * GetWorld()->GetDeltaSeconds();
	FRotator NewRotation = FRotator(RotationAngle, 0, 0);

	if (CheckForCollision())
	{
		GetWorldTimerManager().ClearTimer(AxeThrowTimerHandle);
		return;
	}
	
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

bool AOmniWeapon_ThrowingAxe::CheckForCollision()
{
	FVector CurrentLocation = GetActorLocation();
	float CollisionRadius = 10.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<FHitResult> HitResults;
	if (UKismetSystemLibrary::SphereTraceMulti(
			GetWorld(),
			CurrentLocation,
			CurrentLocation,
			CollisionRadius,
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3),
			false,
			IgnoredActors,
			EDrawDebugTrace::ForDuration,
			HitResults,
			true
		))
	{
		DRAW_SPHERE_RADIUS(CurrentLocation, CollisionRadius);
		for (const FHitResult& HitResult : HitResults)
		{
			if (HitResult.GetActor())
			{
				AActor* HitActor = HitResult.GetActor();
				UPrimitiveComponent* HitComponent = HitResult.GetComponent();
				if (HitComponent && HitComponent->GetCollisionObjectType() == ECC_Destructible)
				{
					//TODO: If it's destructible, destroy it but do not stop the axe
					PRINT_DEBUG_MESSAGE(5.f, FColor::Purple, FString("Hit Destructible"));
				}
				else if (HitComponent && (HitComponent->GetCollisionObjectType() == ECC_WorldStatic ||
					HitComponent->GetCollisionObjectType() == ECC_WorldDynamic))
				{
					SetActorLocation(HitResult.ImpactPoint);
					SetActorRotation(CalculateLodgedRotation(HitResult.ImpactNormal));
					return true;
				}
				else if (HitComponent && HitComponent->GetCollisionObjectType() == ECC_GameTraceChannel1)
				{
					PRINT_DEBUG_MESSAGE(5.f, FColor::Purple, FString("Hit Character"));
				}
			}
		}
	}

	return false;
}

FRotator AOmniWeapon_ThrowingAxe::CalculateLodgedRotation(const FVector& tHitNormal) const
{
	FVector AxeForward = GetActorForwardVector();
	FVector RotationAxis = FVector::CrossProduct(AxeForward, tHitNormal).GetSafeNormal();
	float RotationAngle = FMath::Acos(FVector::DotProduct(AxeForward, tHitNormal));
	FQuat AlignQuat = FQuat(RotationAxis, RotationAngle);

	// Apply a 180-degree rotation around the Y-axis
	FQuat RotationAroundY = FQuat(FVector(0, 1, 0), FMath::DegreesToRadians(180.0f));
	FQuat FinalQuat = RotationAroundY * AlignQuat;

	return FinalQuat.Rotator();
}
