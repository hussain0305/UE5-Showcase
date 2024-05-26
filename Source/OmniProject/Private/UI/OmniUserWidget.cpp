// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/OmniHUD.h"

void UOmniUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Setup Controller callback
	AOmniHUD* OmniHUD = Cast<AOmniHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (OmniHUD)
	{
		OmniHUD->OnControllerAssigned.AddDynamic(this, &UOmniUserWidget::HUDControllerInitialized);
	}
}

void UOmniUserWidget::HUDControllerInitialized(UOmniHUDController* Controller)
{
	if (Controller == nullptr)
	{
		return;
	}

	HUDController = Controller;
	StartListening();
}

void UOmniUserWidget::StartListening()
{
	InitHUDValue();
	BindListenerDelegate();
}

void UOmniUserWidget::InitHUDValue() {}
void UOmniUserWidget::BindListenerDelegate() {}
void UOmniUserWidget::UpdateValue(float newValue) {}
