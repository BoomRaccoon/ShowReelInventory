// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputModifierBoolNegate.h"

FInputActionValue UInputModifierBoolNegate::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
		return CurrentValue.GetMagnitude();	
}