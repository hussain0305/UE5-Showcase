// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OmniWeapon_Axe.h"

#include "Character/OmniCharacter.h"
#include "Weapons/OmniWeapon_ThrowingAxe.h"

void AOmniWeapon_Axe::PerformSecondaryAction(TObjectPtr<AOmniCharacter> OwningCharacter)
{
	Super::PerformSecondaryAction(OwningCharacter);

	FVector Origin, Target;
	// USkeletalMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	// if (MeshComponent)
	// {
	// 	Origin = MeshComponent->GetSocketLocation("SingleHandedWeapon");
	// }
	Origin = GetActorLocation();

	APlayerController* PlayerController = Cast<APlayerController>(OwningCharacter->GetController());
	if (PlayerController)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector CameraForwardVector = CameraRotation.Vector();
		FVector MaxDistancePoint = Origin + (CameraForwardVector * ThrowRange);

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		CollisionParams.AddIgnoredActor(OwningCharacter);
		
		if (bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Origin, MaxDistancePoint, ECC_Visibility, CollisionParams))
		{
			Target = HitResult.Location;
		}
		else
		{
			Target = MaxDistancePoint;
		}
		Target = MaxDistancePoint;
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
			ThrownAxe->StartThrowTrajectory(Origin, Target);
		}
	}
}
