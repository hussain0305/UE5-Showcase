// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniHUD.h"
#include "Blueprint/UserWidget.h"
#include "HeaderFiles/DebugMacros.h"
#include "UI/OmniHUDController.h"
#include "UI/OmniUserWidget.h"

void AOmniHUD::InitializeHUD(FOmniWidgetControllerParams& PlayerDetails)
{
	UUserWidget* OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), BP_HUDOverlay);
	HUDOverlayWidget = Cast<UOmniUserWidget>(OverlayWidget);
	HUDOverlayWidget->AddToViewport();

	HUDController = NewObject<UOmniHUDController>(this, UOmniHUDController::StaticClass());
	HUDController->InitController(PlayerDetails);

	OnControllerAssigned.Broadcast(HUDController);
}

UOmniHUDController* AOmniHUD::GetHUDController() const
{
	return HUDController;
}