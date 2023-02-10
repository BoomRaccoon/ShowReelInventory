// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "InputModifierBoolNegate.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UInputModifierBoolNegate : public UInputModifier
{
	GENERATED_BODY()


	
protected:
	FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;

};
