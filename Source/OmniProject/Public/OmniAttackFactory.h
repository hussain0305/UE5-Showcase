// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OmniAttackFactory.generated.h"

class UOmniAttack;
/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UOmniAttackFactory : public UObject
{
	GENERATED_BODY()
	
public:
	UOmniAttack* CreateAttackInstance(TSubclassOf<UOmniAttack> AttackClass, UObject* Outer);
};
