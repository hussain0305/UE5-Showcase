// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameModeBase.h"
#include "Character/OmniCharacter.h"
#include "Game/OmniGameInstance.h"
#include "HeaderFiles/OmniGameplayEffectsTable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmniController.h"
#include "Player/OmniPlayerState.h"

AOmniGameModeBase::AOmniGameModeBase()
{
	//Assign a default pawn 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Blueprints_Character/BaseCharacter_Medieval.BaseCharacter_Medieval"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	PlayerControllerClass = AOmniController::StaticClass();
	PlayerStateClass = AOmniPlayerState::StaticClass();
}

void AOmniGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World= GetWorld();
	if (World == nullptr)
	{
		return;
	}

	APlayerController* LocPlayerController = World->GetFirstPlayerController();
	if (LocPlayerController == nullptr)
	{
		return;
	}

	// Check if a pawn has been selected in the character selection class and assign that if available
	if (const TObjectPtr<UOmniGameInstance> GameInstance = Cast<UOmniGameInstance>(UGameplayStatics::GetGameInstance(World)))
	{
		if (const TSubclassOf<AOmniCharacter> SelectedCharacterClass = GameInstance->GetLocalPlayerSelectedCharacterClass())
		{
			if(APawn* ExistingPlayerCharacter = LocPlayerController->GetPawn())
			{
				World->DestroyActor(ExistingPlayerCharacter);
			}
			
			const TObjectPtr<AOmniCharacter> SpawnedPlayerCharacter = World->SpawnActor<AOmniCharacter>(SelectedCharacterClass);
			LocPlayerController->Possess(SpawnedPlayerCharacter);
		}
	}
	
	// Is this the proper, industry-standard way to assign input mode? Using UWidgetBlueprintLibrary here doesn't make sense to me
	const FInputModeGameOnly InputModeGameOnly;
	LocPlayerController->SetInputMode(InputModeGameOnly);

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
