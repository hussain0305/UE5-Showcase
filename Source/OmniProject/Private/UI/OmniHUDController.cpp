// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniHUDController.h"
#include "HeaderFiles/DebugMacros.h"
#include "HeaderFiles/OmniPlayerDetails.h"

void UOmniHUDController::InitController(FOmniWidgetControllerParams& ControllerParams)
{
	PlayerController		= ControllerParams.PlayerController;
	PlayerState				= ControllerParams.PlayerState;
	AbilitySystemComponent	= ControllerParams.AbilitySystemComponent;
	AttributeSet			= ControllerParams.AttributeSet;

	PRINT_DEBUG_MESSAGE(5, FColor::Green, FString("EVERYTHINBG INITIALIZED!!!!"));
}

void UOmniHUDController::BroadcastInitialValues()
{
	
}
