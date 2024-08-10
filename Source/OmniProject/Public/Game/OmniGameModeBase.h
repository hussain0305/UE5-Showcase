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
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* GameplayEffectsDatabase;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* WeaponConfigurationsDatabase;

	UFUNCTION(BlueprintCallable)
	bool GetGameplayEffectDetails(FName RowName, FOmniGameplayEffectsDatabase& DatabaseRow);

	UFUNCTION(BlueprintCallable)
	bool GetWeaponConfiguration(FName RowName, EWeaponType WeaponType, FOmniWeaponTable& WeaponConfig);
};

