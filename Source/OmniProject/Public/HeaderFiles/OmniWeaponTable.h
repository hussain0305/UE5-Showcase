#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "OmniGlobal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "OmniWeaponTable.generated.h"


USTRUCT(BlueprintType)
struct FOmniWeaponTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnimationDetails SheathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnimationDetails UnsheathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack")
	FAnimationDetails PrimaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack")
	EAttackSelection PrimaryAttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack", meta = (EditCondition = "PrimaryAttackType == EAttackSelection::Randomized || PrimaryAttackType == EAttackSelection::Combo", EditConditionHides))
	uint8 NumSections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack", meta = (EditCondition = "PrimaryAttackType == EAttackSelection::StateBased", EditConditionHides))
	uint8 RunningAttackSectionNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack", meta = (EditCondition = "PrimaryAttackType == EAttackSelection::StateBased", EditConditionHides))
	uint8 RetreatingAttackSectionNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack", meta = (EditCondition = "PrimaryAttackType == EAttackSelection::StateBased", EditConditionHides))
	uint8 SidewaysAttackSectionNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack", meta = (EditCondition = "PrimaryAttackType == EAttackSelection::StateBased", EditConditionHides))
	uint8 FallingAttackSectionNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack")
	EAttackType SecondaryAttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType != ESecondaryAttack::NotApplicable", EditConditionHides))
	FAnimationDetails SecondaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType == ESecondaryAttack::Aimed", EditConditionHides))
	FName SecondaryAttackMontageSectionName_PrepStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType == ESecondaryAttack::Aimed", EditConditionHides))
	FName SecondaryAttackMontageSectionName_Prepped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType == ESecondaryAttack::Aimed", EditConditionHides))
	FName SecondaryAttackMontageSectionName_Attack;
};