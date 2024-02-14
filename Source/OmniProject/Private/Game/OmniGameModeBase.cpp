// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameModeBase.h"

#include "HeaderFiles/DebugMacros.h"
#include "HeaderFiles/OmniGameplayEffectsTable.h"
#include "Player/OmniController.h"
#include "Player/OmniPlayerState.h"

AOmniGameModeBase::AOmniGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Blueprints_Character/BaseCharacter.BaseCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// FSoftObjectPath GameplayEffectsTablePath = FSoftObjectPath(TEXT("/Game/Data/GameplayEffectsInfo.GameplayEffectsInfo"));
	// if(Cast<UDataTable>(GameplayEffectsTablePath.ResolveObject()))
	// {
	// 	PRINT_DEBUG_MESSAGE(10, FColor::Emerald, FString("DATA TABLE FOUND"));
	// 	GameplayEffectsDatabase = Cast<UDataTable>(GameplayEffectsTablePath.ResolveObject());
	// }
	// else
	// {
	// 	PRINT_DEBUG_MESSAGE(10, FColor::Emerald, FString("NOT FOUND NOT FOUND"));
	// }
	
	PlayerControllerClass = AOmniController::StaticClass();
	PlayerStateClass = AOmniPlayerState::StaticClass();
}

bool AOmniGameModeBase::GetGameplayEffectDetails(FName RowName, FOmniGameplayEffectsDatabase& DatabaseRow)
{
	if (GameplayEffectsDatabase != nullptr)
	{
		FString ContextString;
		if (GameplayEffectsDatabase->FindRow<FOmniGameplayEffectsDatabase>(RowName, ContextString) != nullptr)
		{
			DatabaseRow = *GameplayEffectsDatabase->FindRow<FOmniGameplayEffectsDatabase>(RowName, ContextString);
			return true;
		}
	}
	return false;
}
