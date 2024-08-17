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

	UPROPERTY(EditDefaultsOnly)
	float ThrowRange = 10000;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AOmniWeapon_ThrowingAxe> ThrowingAxe;

	virtual void Secondary_PreAttack(TObjectPtr<AOmniCharacter> OwningCharacter) override;
	
	virtual void Secondary_DoAttack(TObjectPtr<AOmniCharacter> OwningCharacter) override;
};
