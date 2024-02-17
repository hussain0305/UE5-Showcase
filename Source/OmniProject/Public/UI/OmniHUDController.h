// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OmniHUDController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class OMNIPROJECT_API UOmniHUDController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void InitController(FOmniWidgetControllerParams& ControllerParams);

	virtual void BroadcastInitialValues();

protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<UAttributeSet> AttributeSet;

};
