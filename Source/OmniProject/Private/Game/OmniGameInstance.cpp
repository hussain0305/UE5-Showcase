// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameInstance.h"

TSubclassOf<AOmniCharacter> UOmniGameInstance::GetLocalPlayerSelectedCharacterClass() const
{
	return SelectedCharacterClass;
}

void UOmniGameInstance::SetLocalPlayerSelectedCharacterClass(TSubclassOf<AOmniCharacter> CharacterClass)
{
	SelectedCharacterClass = CharacterClass;
}
