// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniHUD.h"
#include "Blueprint/UserWidget.h"
#include "Character/OmniCharacter.h"
#include "HeaderFiles/DebugMacros.h"
#include "Player/OmniController.h"
#include "UI/OmniHUDController.h"
#include "UI/OmniUserWidget.h"
#include "UI/Widgets/WidgetReticle.h"

void AOmniHUD::InitializeHUD(FOmniWidgetControllerParams& PlayerDetailsParam)
{
	PlayerDetails = PlayerDetailsParam;
	
	UUserWidget* OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), BP_HUDOverlay);
	HUDOverlayWidget = Cast<UOmniUserWidget>(OverlayWidget);
	HUDOverlayWidget->AddToViewport();

	ReticleWidget = CreateWidget<UWidgetReticle>(GetWorld(), WBP_Reticle);
	ReticleWidget->AddToViewport();
	ToggleReticle(false);
	
	HUDController = NewObject<UOmniHUDController>(this, UOmniHUDController::StaticClass());
	HUDController->InitController(PlayerDetailsParam);

	OnControllerAssigned.Broadcast(HUDController);

	TrySetupCharacter();
}

UOmniHUDController* AOmniHUD::GetHUDController() const
{
	return HUDController;
}

void AOmniHUD::ToggleReticle(bool ReticleEnabled)
{
	ReticleWidget->SetReticleEnabled(ReticleEnabled);
}

void AOmniHUD::TrySetupCharacter()
{
	//Perhaps not the best approach for this. I call InitializeHUD from Character's PossessedBy function. but the character is not ready at that time and not fetched here. I still added this here just in case
	//If there's no character present, I listen to the Controller broadcasting the character from its possesses() function, which is called after the character is setup and possessed
	
	if (PlayerDetails.PlayerController->GetCharacter())
	{
		SetupCharacter(Cast<AOmniCharacter>(PlayerDetails.PlayerController->GetCharacter()));
	}
	else
	{
		PlayerDetails.PlayerController->OnCharacterPossessionDone.AddDynamic(this, &AOmniHUD::SetupCharacter);
	}
}

void AOmniHUD::SetupCharacter(AOmniCharacter* PlayerCharacterParam)
{
	PlayerCharacter = Cast<AOmniCharacter>(PlayerCharacterParam);
	PlayerCharacter->OnIsAimingChanged.RemoveDynamic(this, &AOmniHUD::ToggleReticle);
	PlayerCharacter->OnIsAimingChanged.AddDynamic(this, &AOmniHUD::ToggleReticle);
}
