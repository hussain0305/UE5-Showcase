// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeaderFiles/OmniGlobal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/OmniWeapon.h"
#include "OmniAttack.generated.h"

UCLASS(Blueprintable)
class OMNIPROJECT_API UOmniAttack : public UObject
{
	GENERATED_BODY()

public:
	
//=============
//Attack Config
//=============

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config")
	EAttackSelection AttackSelection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config")
	EAttackType AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config")
	FAnimationDetails AttackDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config", meta = (EditCondition = "AttackType == EAttackType::RegularAttack", EditConditionHides))
	uint8 AttackSectionNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config", meta = (EditCondition = "AttackType == EAttackType::Aimed", EditConditionHides))
	FName RangedAttackMontageSectionName_PrepStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config", meta = (EditCondition = "AttackType == EAttackType::Aimed", EditConditionHides))
	FName RangedAttackMontageSectionName_Prepped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config", meta = (EditCondition = "AttackType == EAttackType::Aimed", EditConditionHides))
	FName RangedAttackMontageSectionName_Attack;

//===================
//Getters and Setters
//===================

	FORCEINLINE EAttackPhase GetAttackPhase() const{ return AttackPhase; }
	
//=========
//Functions
//=========

	virtual void InitializeAttack();

	UFUNCTION(BlueprintCallable)
	virtual void ProcessPrimaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon);

	UFUNCTION(BlueprintCallable)
	virtual void ProcessPrimaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon);

	UFUNCTION(BlueprintCallable)
	virtual void ProcessSecondaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon);

	UFUNCTION(BlueprintCallable)
	virtual void ProcessSecondaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon);

protected:

	EAttackPhase AttackPhase = EAttackPhase::Ready;
};
