// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HeaderFiles/OmniPlayerDetails.h"
#include "OmniHUD.generated.h"

class AOmniCharacter;
class UOmniHUDController;
class UOmniUserWidget;
class UWidgetReticle;

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

	UPROPERTY(EditDefaultsOnly, Category = "Blueprints")
	TSubclassOf<UWidgetReticle> WBP_Reticle;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWidgetReticle> ReticleWidget;

	UPROPERTY(BlueprintAssignable, Category = "Controller Assigned Delegate")
	FControllerAssignedSignature OnControllerAssigned;

	UFUNCTION()
	void InitializeHUD(FOmniWidgetControllerParams& PlayerDetailsParam);

	UFUNCTION(BlueprintCallable)
	UOmniHUDController* GetHUDController() const;

	UFUNCTION()
	void ToggleReticle(bool ReticleEnabled);
	
protected:
	FOmniWidgetControllerParams PlayerDetails;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOmniHUDController> HUDController;

	TObjectPtr<AOmniCharacter> PlayerCharacter;

	UFUNCTION()
	void TrySetupCharacter();

	UFUNCTION()
	void SetupCharacter(AOmniCharacter* PlayerCharacterParam);
};
