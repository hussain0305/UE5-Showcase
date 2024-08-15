// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/OmniCameraManager.h"
#include "Camera/CameraComponent.h"
#include "Character/OmniCharacter.h"

UOmniCameraManager::UOmniCameraManager(): DefaultFOV(0), ZoomedFOV(0), bWantsToZoom(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UOmniCameraManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void UOmniCameraManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleZoom(DeltaTime);
}

void UOmniCameraManager::SetZoom(bool Value)
{
	bWantsToZoom = Value;
}

void UOmniCameraManager::HandleZoom(float DeltaTime) const
{
	if (CameraComponent)
	{
		const float CurrentFOV = CameraComponent->FieldOfView;
		const float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
		const float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, ZoomInterpSpeed);
		CameraComponent->SetFieldOfView(NewFOV);
	}
}

void UOmniCameraManager::SetupCameraManager(TObjectPtr<UCameraComponent> CameraComponentParam, TObjectPtr<AOmniCharacter> OwnerCharacterParam)
{
	CameraComponent = CameraComponentParam;
	DefaultFOV = CameraComponent->FieldOfView;
	ZoomedFOV = DefaultFOV * ZoomedFOVMultiple;

	OwnerCharacter = OwnerCharacterParam;
	OwnerCharacter->OnIsAimingChanged.RemoveDynamic(this, &UOmniCameraManager::SetZoom);
	OwnerCharacter->OnIsAimingChanged.AddDynamic(this, &UOmniCameraManager::SetZoom);
}

void UOmniCameraManager::SetZoomedFOVMultiple(const float Multiple)
{
	ZoomedFOVMultiple = Multiple;
	ZoomedFOV = DefaultFOV * ZoomedFOVMultiple;
}
