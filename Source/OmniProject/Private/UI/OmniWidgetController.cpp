// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniWidgetController.h"
#include "HeaderFiles/DebugMacros.h"
#include "HeaderFiles/OmniPlayerDetails.h"

void UOmniWidgetController::InitController(FOmniWidgetControllerParams& ControllerParams)
{
	PlayerController		= ControllerParams.PlayerController;
	PlayerState				= ControllerParams.PlayerState;
	AbilitySystemComponent	= ControllerParams.AbilitySystemComponent;
	AttributeSet			= ControllerParams.AttributeSet;
}
