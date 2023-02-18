// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActivatableWidget_Game.h"

TOptional<FUIInputConfig> UActivatableWidget_Game::GetDesiredInputConfig() const
{
	FUIInputConfig InputConfig = FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown, true);
	//GetOwningPlayer()->SetShowMouseCursor(false);
	InputConfig.bIgnoreLookInput = false;
	InputConfig.bIgnoreMoveInput = false;
	return InputConfig;
}
