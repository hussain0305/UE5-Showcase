// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "OmniGameplayEffectActor.generated.h"

class AOmniCharacter;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class OMNIPROJECT_API AOmniGameplayEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOmniGameplayEffectActor();

	virtual void ApplyGameplayEffectTo(AOmniCharacter* TargetCharacter);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect;

	UFUNCTION()
		virtual void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USphereComponent* SphereComponent;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	USceneComponent* Root;
};
