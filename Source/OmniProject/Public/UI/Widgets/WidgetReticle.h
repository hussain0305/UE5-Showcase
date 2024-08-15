// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/OmniUserWidget.h"
#include "WidgetReticle.generated.h"

class UImage;

UCLASS()
class OMNIPROJECT_API UWidgetReticle : public UOmniUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UImage* Reticle;

	UFUNCTION(BlueprintCallable)
	void SetReticleEnabled(bool Enabled);

	UFUNCTION(BlueprintCallable)
	void SetReticleColor(FColor Color);
};
