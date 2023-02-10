// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/GasDevSettings.h"



UGasDevSettings::UGasDevSettings(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	CategoryName = "Editor";
	SectionName = "Ability System Settings";
}
