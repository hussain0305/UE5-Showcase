// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameModeBase.h"

#include "Player/OmniController.h"
#include "Player/OmniPlayerState.h"

AOmniGameModeBase::AOmniGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Blueprints_Character/BaseCharacter.BaseCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AOmniController::StaticClass();
	PlayerStateClass = AOmniPlayerState::StaticClass();
}
