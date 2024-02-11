// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OmniHUD.generated.h"

class UOmniUserWidget;
/**
 * 
 */
UCLASS()
class OMNIPROJECT_API AOmniHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UOmniUserWidget> HUDOverlayWidget;

protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOmniUserWidget> HUDOverlayClass;
};
