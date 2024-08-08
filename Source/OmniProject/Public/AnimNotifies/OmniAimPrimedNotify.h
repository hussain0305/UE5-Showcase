// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/OmniAnimNotify.h"
#include "OmniAimPrimedNotify.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UOmniAimPrimedNotify : public UOmniAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
