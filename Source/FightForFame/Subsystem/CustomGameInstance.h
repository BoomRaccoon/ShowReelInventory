// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UCustomGameInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UCustomGameInstance();

	
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

};
