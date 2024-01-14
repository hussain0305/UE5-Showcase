// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmniGlobal.h"
#include "AnimNotifies/OmniAnimNotify.h"
#include "OmniWeaponUnsheathNotify.generated.h"

UCLASS()
class OMNIPROJECT_API UOmniWeaponUnsheathNotify : public UOmniAnimNotify
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EWeaponType WeaponType;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
