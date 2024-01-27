// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/OmniItem.h"
#include "OmniWeapon.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class OMNIPROJECT_API AOmniWeapon : public AOmniItem
{
	GENERATED_BODY()

public:
	AOmniWeapon();

//=====================================
//Public Pointers, Variables and Fields
//=====================================

	UPROPERTY(EditAnywhere, Category = "Character Item Component")
		TObjectPtr<UStaticMeshComponent> ScabbardMesh;

	UPROPERTY(EditDefaultsOnly, Category= "Weapon Details")
		EWeaponType WeaponType;

	//-----------------
	// Weapon Hit Trace
	//-----------------
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Trace")
		UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
		USceneComponent* WeaponTraceTransforms;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
		USceneComponent* WeaponTraceStart;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
		USceneComponent* WeaponTraceEnd;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Trace")
		FVector WeaponHitTraceSize = FVector(2.f,2.f,2.f);

	//-----------------
	// Weapon Hit Trace
	//-----------------
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		int NumAttackOptions = 1;

	//-------------------
	// Animation Montages
	//-------------------
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation|Primary Action")
		UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation|Weapon Handling")
		UAnimMontage* SheathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation|Weapon Handling")
		UAnimMontage* UnsheathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation|Secondary Action")
		UAnimMontage* SecondaryActionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation|Secondary Action")
		FName SecondaryActionMontage_Aim;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation|Secondary Action")
		FName SecondaryActionMontage_Attack;
	
//=========
//Functions
//=========

	virtual void SetItemState(const EItemState NewState) override;
	
protected:

	virtual void BeginPlay() override;
	
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
		virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
