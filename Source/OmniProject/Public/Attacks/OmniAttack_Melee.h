// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attacks/OmniAttack.h"
#include "OmniAttack_Melee.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UOmniAttack_Melee : public UOmniAttack
{
	GENERATED_BODY()

public:
	
	virtual void ProcessPrimaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	virtual void ProcessPrimaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	virtual void ProcessSecondaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	virtual void ProcessSecondaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;
};
