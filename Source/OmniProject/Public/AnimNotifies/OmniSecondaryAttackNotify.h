// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/OmniAnimNotify.h"
#include "OmniSecondaryAttackNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSecondaryAttackNotify);

UCLASS()
class OMNIPROJECT_API UOmniSecondaryAttackNotify : public UOmniAnimNotify
{
	GENERATED_BODY()

public:
	FOnSecondaryAttackNotify OnSecondaryAttackNotify;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
