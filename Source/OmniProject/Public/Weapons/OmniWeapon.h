// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/OmniItem.h"
#include "HeaderFiles/OmniWeaponTable.h"
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

	UPROPERTY(EditDefaultsOnly, Category= "Weapon Details")
	FName WeaponID;

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
	
//=========
//Functions
//=========

	//---------------
	// Action Helpers
	//---------------
	FORCEINLINE void SetIsWeaponAttacking(const bool Attacking) { bIsAttacking = Attacking;}
	FORCEINLINE bool GetIsWeaponAttacking() const {return bIsAttacking;}

	//-------
	// Others
	//-------
	virtual void SetItemState(const EItemState NewState) override;

	UFUNCTION(BlueprintCallable)
	int32 GetMontageSectionToPlay(ECharacterLocomotionState LocomotionState);

	UFUNCTION(BlueprintCallable)
	FOmniWeaponTable GetWeaponConfig();

	virtual void Secondary_PreAttack(TObjectPtr<class AOmniCharacter> OwningCharacter);
	virtual void Secondary_DoAttack(TObjectPtr<class AOmniCharacter> OwningCharacter);
	virtual void Secondary_PostAttack(TObjectPtr<class AOmniCharacter> OwningCharacter);

protected:

	virtual void BeginPlay() override;
	
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AssertWeaponConfig();

private:
	//---------------------
	// Weapon Configuration
	//---------------------

	FOmniWeaponTable WeaponConfig;
	bool WeaponConfigFetched = false;
	bool bIsAttacking = false;
};
