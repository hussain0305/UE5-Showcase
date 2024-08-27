// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/OmniItem.h"
#include "HeaderFiles/OmniWeaponTable.h"
#include "OmniWeapon.generated.h"

class UOmniAttack;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS(Abstract, Blueprintable)
class OMNIPROJECT_API AOmniWeapon : public AOmniItem
{
	GENERATED_BODY()

public:
	AOmniWeapon();
//=============
//Weapon Config
//=============
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	FName WeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	FAnimationDetails SheathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	FAnimationDetails UnsheathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config|Primary Attack")
	EAttackType PrimaryAttackType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config|Primary Attack", meta = (EditCondition = "PrimaryAttackType != EAttackType::NotApplicable", EditConditionHides))
	FAttackConfiguration PrimaryAttack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config|Secondary Attack")
	EAttackType SecondaryAttackType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config|Secondary Attack", meta = (EditCondition = "SecondaryAttackType != EAttackType::NotApplicable", EditConditionHides))
	FAttackConfiguration SecondaryAttack;

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
	
//=========
//Functions
//=========

	//--------------------
	// Getters and Setters
	//--------------------

	//-------
	// Others
	//-------
	virtual void SetItemState(const EItemState NewState) override;

	UFUNCTION(BlueprintCallable)
	int32 GetMontageSectionToPlay(ECharacterLocomotionState LocomotionState);
	
	UFUNCTION(BlueprintCallable)
	virtual void ProcessPrimaryInput_Start();

	UFUNCTION(BlueprintCallable)
	virtual void ProcessPrimaryInput_Stop();

	UFUNCTION(BlueprintCallable)
	virtual void ProcessSecondaryInput_Start();

	UFUNCTION(BlueprintCallable)
	virtual void ProcessSecondaryInput_Stop();

	UFUNCTION(BlueprintCallable)
	FOmniWeaponTable GetWeaponConfig();

	UFUNCTION(BlueprintCallable)
	void SetInputConsumers(EWeaponAction Primary, EWeaponAction Secondary);
	
protected:
	
	TObjectPtr<UOmniAttack> PrimaryInputConsumer;
	TObjectPtr<UOmniAttack> SecondaryInputConsumer;
	
	virtual void BeginPlay() override;
	void InitializeAttacks();

	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AssertWeaponConfig();

private:
	FOmniWeaponTable WeaponConfig;
	bool WeaponConfigFetched = false;
};
