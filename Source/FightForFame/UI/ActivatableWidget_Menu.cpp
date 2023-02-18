// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActivatableWidget_Menu.h"

TOptional<FUIInputConfig> UActivatableWidget_Menu::GetDesiredInputConfig() const
{
	FUIInputConfig InvConfig = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, false);
	//GetOwningPlayer()->SetShowMouseCursor(true);
	InvConfig.bIgnoreMoveInput = bIgnoreMovement;
	InvConfig.bIgnoreLookInput = bIgnoreLook;
	return InvConfig;
}
