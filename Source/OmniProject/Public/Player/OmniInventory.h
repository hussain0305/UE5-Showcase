// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OmniGlobal.h"
#include "Weapons/OmniWeapon.h"
#include "OmniInventory.generated.h"

class AOmniWeapon;

UCLASS()
class OMNIPROJECT_API UOmniInventory : public UObject
{
	GENERATED_BODY()
	
public:
	
//==================================
//Setters, Getters, Inline Functions
//==================================

	//---------------------------------------------------------------------
	// Inventory Helpers - Weapons currently being carried by the character
	//---------------------------------------------------------------------
	FORCEINLINE bool GetIsCarryingOneHandedWeapon() const {return OneHandedWeapon != nullptr;}
	FORCEINLINE bool GetIsCarryingTwoHandedWeapon() const {return TwoHandedWeapon != nullptr;}
	FORCEINLINE void SetCarriedOneHandedWeapon(const TObjectPtr<AOmniWeapon> CarriedWeapon) {OneHandedWeapon = CarriedWeapon;}
	FORCEINLINE void SetCarriedTwoHandedWeapon(const TObjectPtr<AOmniWeapon> CarriedWeapon) {TwoHandedWeapon = CarriedWeapon;}
	FORCEINLINE bool GetHasWeaponOfType(const TObjectPtr<AOmniWeapon> WeaponToPickup) const {return GetCurrentlyCarriedWeaponOfType(WeaponToPickup) != nullptr;}
	FORCEINLINE TObjectPtr<AOmniWeapon> GetCurrentlyCarriedWeaponOfType(const TObjectPtr<AOmniWeapon> Weapon) const {return (Weapon->WeaponType == EWeaponType::OneHandedWeapon ? OneHandedWeapon : TwoHandedWeapon);}

	void SetCarriedWeapon(TObjectPtr<AOmniWeapon> Weapon);
	void SetCarriedWeapon(EWeaponType WeaponType, TObjectPtr<AOmniWeapon> Weapon);
private:
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<AOmniWeapon> OneHandedWeapon;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<AOmniWeapon> TwoHandedWeapon;

};
