// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OmniInventory.h"

void UOmniInventory::SetWeaponInInventory(TObjectPtr<AOmniWeapon> Weapon)
{
	if (Weapon != nullptr)
	{
		SetWeaponInInventory(Weapon->WeaponType, Weapon);
	}
}

void UOmniInventory::SetWeaponInInventory(EWeaponType WeaponType, TObjectPtr<AOmniWeapon> Weapon)
{
	switch (WeaponType)
	{
		case EWeaponType::OneHandedWeapon:
			if(OneHandedWeapon != nullptr)
			{
				//Something has gone wrong, might need to do something
			}
			OneHandedWeapon = Weapon;
			break;

		case EWeaponType::TwoHandedWeapon:
			if(TwoHandedWeapon != nullptr)
			{
				//Something has gone wrong, might need to do something
			}
			TwoHandedWeapon = Weapon;
			break;
		default:
			break;
	}
}
