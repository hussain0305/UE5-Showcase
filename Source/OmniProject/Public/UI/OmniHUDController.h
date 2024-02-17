// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmniHUDController.generated.h"

struct FOnAttributeChangeData;
class AOmniController;
class AOmniPlayerState;
class UOmniAttributeSet;
class UOmniAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

UCLASS()
class OMNIPROJECT_API UOmniHUDController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void InitController(FOmniWidgetControllerParams& ControllerParams);

	void BroadcastInitialValues() const;
	void SetupCallbacksAndDelegates();

protected:

//=================
//Controller Fields
//=================
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<AOmniController> PlayerController;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<AOmniPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<UOmniAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		TObjectPtr<UOmniAttributeSet> AttributeSet;
	
//================================
//Broadcasters And Bound Functions
//================================
	UPROPERTY(BlueprintAssignable, Category = "Attribute Change Delegate")
		FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Attribute Change Delegate")
		FOnMaxHealthChangedSignature OnMaxHealthChanged;

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
