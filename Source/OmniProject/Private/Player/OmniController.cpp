// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OmniController.h"
#include "Character/OmniCharacter.h"

void AOmniController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnCharacterPossessionDone.Broadcast(Cast<AOmniCharacter>(InPawn));
}
