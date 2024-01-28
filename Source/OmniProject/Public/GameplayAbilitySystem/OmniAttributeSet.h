// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "OmniAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class OMNIPROJECT_API UOmniAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UOmniAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
//====================================
//Attributes and their OnRep functions
//====================================
	//--------
	// Health
	//--------
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Character Attributes")
		FGameplayAttributeData Health;
		ATTRIBUTE_ACCESSORS(UOmniAttributeSet, Health);
	UFUNCTION()
		void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	//-----------
	// Max Health
	//-----------
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Character Attributes")
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS(UOmniAttributeSet, MaxHealth);
	UFUNCTION()
		void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
};
