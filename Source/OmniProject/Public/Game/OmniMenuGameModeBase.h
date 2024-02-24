// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmniMenuGameModeBase.generated.h"

UCLASS()
class OMNIPROJECT_API AOmniMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Main Menu")
		TSubclassOf<UUserWidget> BP_MainMenu;

protected:

	TObjectPtr<UUserWidget> MainMenu;
};
