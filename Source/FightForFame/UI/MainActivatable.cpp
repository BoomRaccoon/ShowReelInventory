// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainActivatable.h"

TOptional<FUIInputConfig> UMainActivatable::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
}