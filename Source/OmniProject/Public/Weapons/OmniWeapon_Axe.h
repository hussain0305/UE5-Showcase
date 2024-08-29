// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/OmniWeapon.h"
#include "OmniWeapon_Axe.generated.h"

class AOmniWeapon_ThrowingAxe;
/**
 * 
 */
UCLASS()
class OMNIPROJECT_API AOmniWeapon_Axe : public AOmniWeapon
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	float ThrowRange = 10000;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AOmniWeapon_ThrowingAxe> ThrowingAxe;

	UFUNCTION()
	void ReleaseAxe();

	virtual void ProcessPrimaryInput_Start() override;

	virtual void ProcessSecondaryInput_Start() override;

	void RecallAxe();

	void AxeRecallComplete();
private:

	void SubscribeToBroadcasts();

	UPROPERTY()
	TObjectPtr<AOmniWeapon_ThrowingAxe> ThrownAxe;
};
