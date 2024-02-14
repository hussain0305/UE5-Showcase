// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmniUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UOmniUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetWidgetController(const TObjectPtr<UOmniWidgetController> Controller) { WidgetController = Controller; }

	UFUNCTION(BlueprintCallable)
		UOmniWidgetController* GetWidgetController() { return WidgetController;}

private:
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UOmniWidgetController> WidgetController;
};
