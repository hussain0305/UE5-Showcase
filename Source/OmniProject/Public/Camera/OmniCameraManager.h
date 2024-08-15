// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OmniCameraManager.generated.h"


class AOmniCharacter;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIPROJECT_API UOmniCameraManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOmniCameraManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomInterpSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomedFOVMultiple = 0.8 ;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetZoom(bool Value);
	
	void HandleZoom(float DeltaTime) const;

	void SetupCameraManager(TObjectPtr<UCameraComponent> CameraComponentParam, TObjectPtr<AOmniCharacter> OwnerCharacterParam);

	//TODO: Added this function because I might want different weapons to offer different levels of zoom. Add a broadcast in each weapon or the character class as it picks up a weapon, to broadcast that weapon's zoom multiple
	UFUNCTION(BlueprintCallable)
	void SetZoomedFOVMultiple(const float Multiple);
	
private:
	TObjectPtr<UCameraComponent> CameraComponent;
	TObjectPtr<AOmniCharacter> OwnerCharacter;
	
	float DefaultFOV;
	float ZoomedFOV;
	bool bWantsToZoom;
};
