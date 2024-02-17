#pragma once

#include "CoreMinimal.h"
#include "OmniPlayerDetails.generated.h"

class UOmniAbilitySystemComponent;
class UOmniAttributeSet;
class AOmniPlayerState;
class AOmniController;

USTRUCT(BlueprintType)
struct FOmniWidgetControllerParams
{
	GENERATED_USTRUCT_BODY()

	FOmniWidgetControllerParams() {}
	FOmniWidgetControllerParams(AOmniController* PlayerControllerParam, AOmniPlayerState* PlayerStateParam, UOmniAttributeSet* AttributeSetParam, UOmniAbilitySystemComponent* AbilitySystemParam)
	: PlayerController(PlayerControllerParam), PlayerState(PlayerStateParam), AttributeSet(AttributeSetParam), AbilitySystemComponent(AbilitySystemParam) {}
	
	UPROPERTY()
		TObjectPtr<AOmniController> PlayerController;

	UPROPERTY()
		TObjectPtr<AOmniPlayerState> PlayerState;

	UPROPERTY()
		TObjectPtr<UOmniAttributeSet> AttributeSet;

	UPROPERTY()
		TObjectPtr<UOmniAbilitySystemComponent> AbilitySystemComponent;
};