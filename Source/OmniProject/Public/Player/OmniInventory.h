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
	FORCEINLINE bool GetHasOneHandedWeaponInInventory() const {return OneHandedWeapon != nullptr;}
	FORCEINLINE bool GetHasTwoHandedWeaponInInventory() const {return TwoHandedWeapon != nullptr;}
	FORCEINLINE void SetOneHandedWeaponInInventory(const TObjectPtr<AOmniWeapon> CarriedWeapon) {OneHandedWeapon = CarriedWeapon;}
	FORCEINLINE void SetTwoHandedWeaponInInventory(const TObjectPtr<AOmniWeapon> CarriedWeapon) {TwoHandedWeapon = CarriedWeapon;}
	FORCEINLINE void SetWieldedWeapon(const TObjectPtr<AOmniWeapon> WieldedWeapon) {CurrentlyWieldedWeapon = WieldedWeapon;}
	FORCEINLINE bool GetHasWeaponOfTypeInInventory(const EWeaponType WeaponType) const {return GetWeaponOfTypeInInventory(WeaponType) != nullptr;}
	FORCEINLINE bool GetIsWieldingWeaponOfDifferentType(const EWeaponType WeaponType) const {return CurrentlyWieldedWeapon != nullptr && CurrentlyWieldedWeapon->WeaponType != WeaponType;}
	FORCEINLINE bool GetWieldedWeaponDropped(const TObjectPtr<AOmniWeapon> DroppedWeapon) const {return CurrentlyWieldedWeapon != nullptr && CurrentlyWieldedWeapon == DroppedWeapon;}
	FORCEINLINE TObjectPtr<AOmniWeapon> GetWeaponOfTypeInInventory(const EWeaponType WeaponType) const {return (WeaponType == EWeaponType::OneHandedWeapon ? OneHandedWeapon : TwoHandedWeapon);}
	FORCEINLINE TObjectPtr<AOmniWeapon> GetWieldedWeapon() const {return CurrentlyWieldedWeapon;}

	void SetWeaponInInventory(TObjectPtr<AOmniWeapon> Weapon);
	void SetWeaponInInventory(EWeaponType WeaponType, TObjectPtr<AOmniWeapon> Weapon);
private:
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<AOmniWeapon> OneHandedWeapon;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<AOmniWeapon> TwoHandedWeapon;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<AOmniWeapon> CurrentlyWieldedWeapon;

};
