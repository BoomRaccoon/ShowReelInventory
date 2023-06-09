// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ActivatableWidget_Game.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UActivatableWidget_Game : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

};
