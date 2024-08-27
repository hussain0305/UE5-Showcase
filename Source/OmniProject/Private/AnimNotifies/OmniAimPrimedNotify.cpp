// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/OmniAimPrimedNotify.h"
#include "Character/OmniCharacter.h"
#include "HeaderFiles/DebugMacros.h"

void UOmniAimPrimedNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (OnAimPrimedNotify.IsBound())
	{
		OnAimPrimedNotify.Broadcast();
	}
}
