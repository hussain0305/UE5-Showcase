// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HeaderFiles/OmniPlayerDetails.h"
#include "OmniHUD.generated.h"

class UOmniWidgetController;
class UOmniUserWidget;
/**
 * 
 */
UCLASS()
class OMNIPROJECT_API AOmniHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Blueprints")
		TSubclassOf<UOmniUserWidget> BP_HUDOverlay;

	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<UOmniUserWidget> HUDOverlayWidget;

	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<UOmniWidgetController> WidgetController;


	UFUNCTION()
		void InitializeHUD(FOmniWidgetControllerParams& PlayerDetails);
protected:

	virtual void BeginPlay() override;
};
