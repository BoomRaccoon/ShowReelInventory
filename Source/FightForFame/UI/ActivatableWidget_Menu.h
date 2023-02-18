// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ActivatableWidget_Menu.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UActivatableWidget_Menu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Input")
	bool bIgnoreMovement = true;
	
	UPROPERTY(EditAnywhere, Category="Input")
	bool bIgnoreLook = true;
	

	TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

};
