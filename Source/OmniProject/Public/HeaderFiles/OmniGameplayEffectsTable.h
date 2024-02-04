#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "OmniGameplayEffectsTable.generated.h"

USTRUCT(BlueprintType)
struct FOmniGameplayEffectsDatabase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EGameplayModOp::Type> ModOp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ModifierMagnitude;
};