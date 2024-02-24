// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameModeBase.h"

#include "Game/OmniGameInstance.h"
#include "HeaderFiles/DebugMacros.h"
#include "HeaderFiles/OmniGameplayEffectsTable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmniController.h"
#include "Player/OmniPlayerState.h"

AOmniGameModeBase::AOmniGameModeBase()
{
	//Assign a default pawn 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Blueprints_Character/BaseCharacter.BaseCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Check if a pawn has been selected in the character selection class and assign that if available
	// if (TObjectPtr<UOmniGameInstance> GameInstance = Cast<UOmniGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	// {
	// 	EOmniCharacterClass SelectedCharacterClass = GameInstance->GetLocalPlayerSelectedCharacterClass();
	// 	if (SelectedCharacterClass != EOmniCharacterClass::None)
	// 	{
	// 		
	// 	}
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
