#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "OmniPlayerDetails.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FOmniWidgetControllerParams
{
	GENERATED_USTRUCT_BODY()

	FOmniWidgetControllerParams() {}
	FOmniWidgetControllerParams(APlayerController* PlayerControllerParam, APlayerState* PlayerStateParam, UAttributeSet* AttributeSetParam, UAbilitySystemComponent* AbilitySystemParam)
	: PlayerController(PlayerControllerParam), PlayerState(PlayerStateParam), AttributeSet(AttributeSetParam), AbilitySystemComponent(AbilitySystemParam) {}
	
	UPROPERTY()
		TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
		TObjectPtr<APlayerState> PlayerState;

	UPROPERTY()
		TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};