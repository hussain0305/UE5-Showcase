// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HeaderFiles/OmniPlayerDetails.h"
#include "OmniHUD.generated.h"

class UOmniHUDController;
class UOmniUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControllerAssignedSignature, UOmniHUDController*, Controller);

UCLASS()
class OMNIPROJECT_API AOmniHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Blueprints")
		TSubclassOf<UOmniUserWidget> BP_HUDOverlay;

	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<UOmniUserWidget> HUDOverlayWidget;
	
	UFUNCTION()
		void InitializeHUD(FOmniWidgetControllerParams& PlayerDetails);

	UFUNCTION(BlueprintCallable)
		UOmniHUDController* GetHUDController() const;

	UPROPERTY(BlueprintAssignable, Category = "Controller Assigned Delegate")
		FControllerAssignedSignature OnControllerAssigned;
	
protected:
	
	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<UOmniHUDController> HUDController;

};
