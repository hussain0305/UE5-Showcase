// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/OmniWeaponUnsheathNotify.h"
#include "Character/OmniCharacter.h"

void UOmniWeaponUnsheathNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (AOmniCharacter* OmniCharacter = Cast<AOmniCharacter>(Owner))
		{
			OmniCharacter->EquipWeaponOfTypeFromInventory(WeaponType);
		}
	}
}
