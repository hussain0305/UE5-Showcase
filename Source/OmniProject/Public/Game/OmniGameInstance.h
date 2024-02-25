// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HeaderFiles/OmniGlobal.h"
#include "OmniGameInstance.generated.h"

UCLASS()
class OMNIPROJECT_API UOmniGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		TSubclassOf<AOmniCharacter> GetLocalPlayerSelectedCharacterClass() const;

	UFUNCTION(BlueprintCallable)
		void SetLocalPlayerSelectedCharacterClass(TSubclassOf<AOmniCharacter> CharacterClass);

private:
	TSubclassOf<AOmniCharacter> SelectedCharacterClass;
};
