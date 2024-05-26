// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/OmniUserWidget.h"
#include "WidgetHealth.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UWidgetHealth : public UOmniUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void InitHUDValue() override;

	virtual void UpdateValue(float newValue) override;

	virtual void BindListenerDelegate() override;
	
	UFUNCTION(BlueprintImplementableEvent)
		void BP_UpdateValue(float newValue);
};
