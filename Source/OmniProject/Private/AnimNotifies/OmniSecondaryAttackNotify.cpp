// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/OmniSecondaryAttackNotify.h"

#include "Character/OmniCharacter.h"

void UOmniSecondaryAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (AOmniCharacter* OmniCharacter = Cast<AOmniCharacter>(Owner))
		{
			OmniCharacter->SecondaryAttackNotification();
		}
	}
}
