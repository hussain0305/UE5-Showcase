#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "OmniWeaponTable.generated.h"

UENUM(BlueprintType)
enum class EAnimationBodyPart : uint8
{
	FullBody	UMETA(DisplayName = "Full Body"),
	UpperBody	UMETA(DisplayName = "Upper Body"),
	LowerBody	UMETA(DisplayName = "Lower Body"),
};

UENUM(BlueprintType)
enum class EAttackSelection : uint8
{
	Randomized		UMETA(DisplayName = "Randomized"),
	Combo			UMETA(DisplayName = "Combo"),
	StateBased		UMETA(DisplayName = "StateBased")
};

UENUM(BlueprintType)
enum class ESecondaryAttack : uint8
{
	NotApplicable		UMETA(DisplayName = "NotApplicable"),
	Aimed				UMETA(DisplayName = "Aimed"),
	RegularAttack		UMETA(DisplayName = "RegularAttack")
};

USTRUCT(BlueprintType)
struct FAnimationDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAnimationBodyPart BodyPart;
};

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
	ESecondaryAttack SecondaryAttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType != ESecondaryAttack::NotApplicable", EditConditionHides))
	FAnimationDetails SecondaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType == ESecondaryAttack::Aimed", EditConditionHides))
	FName SecondaryAttackMontageSectionName_Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType == ESecondaryAttack::Aimed", EditConditionHides))
	FName SecondaryAttackMontageSectionName_Phase2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secondary Attack", meta = (EditCondition = "SecondaryAttackType == ESecondaryAttack::Aimed", EditConditionHides))
	FName SecondaryAttackMontageSectionName_Phase3;
};