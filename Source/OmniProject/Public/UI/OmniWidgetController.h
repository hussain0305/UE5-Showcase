// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmniWidgetController.generated.h"

class UOmniHUDController;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class OMNIPROJECT_API UOmniWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void InitializeWidget(UOmniHUDController* Controller);

protected:

	TObjectPtr<UOmniHUDController> HUDController;
};
