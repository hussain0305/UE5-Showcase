// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/OmniUserWidget.h"

void AOmniHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), HUDOverlayClass);
	OverlayWidget->AddToViewport();
}
