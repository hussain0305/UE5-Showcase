// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmniGameModeBase.generated.h"



UCLASS()
class OMNIPROJECT_API AOmniGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AOmniGameModeBase();

	UPROPERTY(VisibleAnywhere)
		UDataTable* GameplayEffectsDatabase;

	UFUNCTION(BlueprintCallable)
		bool GetGameplayEffectDetails(FName RowName, FOmniGameplayEffectsDatabase& DatabaseRow);
};

