// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmniUserWidget.generated.h"

class UOmniHUDController;
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

	UFUNCTION(BlueprintCallable)
		UOmniHUDController* GetHUDController() { return HUDController;}

	UFUNCTION(BlueprintCallable)
		void HUDControllerInitialized(UOmniHUDController* Controller);

	UFUNCTION(BlueprintImplementableEvent)
		void StartListening();
protected:

	virtual void NativeConstruct() override;
	
private:
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UOmniWidgetController> WidgetController;

	TObjectPtr<UOmniHUDController> HUDController;
};
