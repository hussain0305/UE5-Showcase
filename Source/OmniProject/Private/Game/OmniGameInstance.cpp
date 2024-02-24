// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/OmniGameInstance.h"

EOmniCharacterClass UOmniGameInstance::GetLocalPlayerSelectedCharacterClass() const
{
	return SelectedCharacterClass;
}

void UOmniGameInstance::SetLocalPlayerSelectedCharacterClass(EOmniCharacterClass CharacterClass)
{
	SelectedCharacterClass = CharacterClass;
}
