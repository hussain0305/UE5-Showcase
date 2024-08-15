// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OmniWeapon_Axe.h"

#include "Character/OmniCharacter.h"
#include "HeaderFiles/DebugMacros.h"
#include "Weapons/OmniWeapon_ThrowingAxe.h"

void AOmniWeapon_Axe::PerformSecondaryAction(TObjectPtr<AOmniCharacter> OwningCharacter)
{
	Super::PerformSecondaryAction(OwningCharacter);

	FVector Origin, Target, HitNormal;

	APlayerController* PlayerController = Cast<APlayerController>(OwningCharacter->GetController());
	Origin = PlayerController->PlayerCameraManager->GetCameraLocation();
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(OwningCharacter);
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(OwningCharacter);
	IgnoredActors.Add(this);
	
	if (PlayerController)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector CameraForwardVector = CameraRotation.Vector();
		FVector MaxDistancePoint = Origin + (CameraForwardVector * ThrowRange);

		FHitResult HitResult;

		if (bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Origin, MaxDistancePoint, ECC_Visibility, CollisionParams))
		{
			if (AActor* HitActor = HitResult.GetActor())
			{
				PRINT_DEBUG_MESSAGE_WITH_PARAMETER(5.f, FColor::Emerald, FString("Hit object: "), *HitActor->GetName());
			}
			Target = HitResult.ImpactPoint;
			HitNormal = HitResult.ImpactNormal;
		}
		else
		{
			Target = MaxDistancePoint;
		}
	}
	else
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;

		SpawnParams.Owner = OwningCharacter;
		SpawnParams.Instigator = GetInstigator();

		if (AActor* SpawnedActor = World->SpawnActor<AActor>(ThrowingAxe, SpawnLocation, SpawnRotation, SpawnParams))
		{
			AOmniWeapon_ThrowingAxe* ThrownAxe = Cast<AOmniWeapon_ThrowingAxe>(SpawnedActor);
			ThrownAxe->StartThrowTrajectory(Origin, Target, HitNormal, IgnoredActors);
			ThrownAxe->SetItemState(EItemState::Thrown);
		}
	}
}
