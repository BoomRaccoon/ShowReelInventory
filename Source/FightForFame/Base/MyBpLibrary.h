// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBpLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UMyBpLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static float GetXYDistance(const FVector Object1, const FVector Object2);	
};
