// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameModeBase.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
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

void AOmniGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (const UWorld* World= GetWorld())
	{
		// Is this the proper, industry-standard way to do this? Using UWidgetBlueprintLibrary here doesn't make sense to me
		if (APlayerController* LocPlayerController = World->GetFirstPlayerController())
		{
			const FInputModeGameOnly InputModeGameOnly;
			LocPlayerController->SetInputMode(InputModeGameOnly);
		}
	}
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
