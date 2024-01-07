// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/OmniItem.h"
#include "OmniWeapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class OMNIPROJECT_API AOmniWeapon : public AOmniItem
{
	GENERATED_BODY()

public:
	AOmniWeapon();
	
	UPROPERTY(EditAnywhere, Category = "Character Item Component")
		TObjectPtr<UStaticMeshComponent> SheathMesh;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon Details")
		EWeaponType WeaponType;
	
protected:

	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
