// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attacks/OmniAttack.h"
#include "OmniAttack_AimAndThrow.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UOmniAttack_AimAndThrow : public UOmniAttack
{
	GENERATED_BODY()
	
public:

	virtual void InitializeAttack() override;
	
	virtual void ProcessPrimaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	virtual void ProcessPrimaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	virtual void ProcessSecondaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	virtual void ProcessSecondaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon) override;

	UFUNCTION()
	void SecondaryAttackPrepped();
	
	bool IsAimAnimationPlaying() const;
	void StopAim();
	void SubscribeToBroadcasts();

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AOmniCharacter> Wielder_Cached;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AOmniWeapon> Weapon_Cached;
};
