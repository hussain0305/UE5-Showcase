// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/WidgetReticle.h"
#include "Components/Image.h"

void UWidgetReticle::SetReticleEnabled(bool Enabled)
{
	Reticle->SetVisibility(Enabled ? ESlateVisibility::Visible:ESlateVisibility::Hidden);
}

void UWidgetReticle::SetReticleColor(FColor Color)
{
	Reticle->SetColorAndOpacity(Color);
}
