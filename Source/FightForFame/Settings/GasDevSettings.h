// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GasDevSettings.generated.h"


/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UGasDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
	UGasDevSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	/* What is name for the default weapon socket that will be used
	** to use as the start when no socket is given
	*/
	UPROPERTY(EditAnywhere)
	FName WeaponStartSocket;


	/* What is name for the default weapon socket that will be used
	** to use as the end when no socket is given
	*/
	UPROPERTY(EditAnywhere)
	FName WeaponEndSocket;
};
