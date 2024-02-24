// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniMenuGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void AOmniMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		MainMenu = CreateWidget<UUserWidget>(World, BP_MainMenu);
		MainMenu->AddToViewport();

		// Is this the proper, industry-standard way to do this?
		const FInputModeUIOnly InputModeUIOnly;
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeUIOnly);
	}
}
