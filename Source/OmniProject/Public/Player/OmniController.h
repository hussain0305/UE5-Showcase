// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmniController.generated.h"

class AOmniCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterPossessed, AOmniCharacter*, OmniCharacter);

UCLASS()
class OMNIPROJECT_API AOmniController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void OnPossess(APawn* InPawn) override;

	FCharacterPossessed OnCharacterPossessionDone;
};
