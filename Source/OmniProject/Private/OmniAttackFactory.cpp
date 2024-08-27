// Fill out your copyright notice in the Description page of Project Settings.


#include "OmniAttackFactory.h"

#include "Attacks/OmniAttack.h"

UOmniAttack* UOmniAttackFactory::CreateAttackInstance(TSubclassOf<UOmniAttack> AttackClass, UObject* Outer)
{
	if (AttackClass)
	{
		return NewObject<UOmniAttack>(Outer, AttackClass);
	}
	return nullptr;
}
