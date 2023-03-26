// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_UI.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UFL_UI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="File Utils", meta=(Keywords="file time get modified"))
	static FDateTime GetFileModificationTime(FString Path);

	UFUNCTION(BlueprintCallable, Category="EIS", meta=(Keywords="eis save player mappable"))
	static void WritePlayerMappableKeys(AFightForFameCharacter* Player);

	UFUNCTION(BlueprintCallable, Category = "Memory Management", meta = (Keywords = "force garbage collection"))
	static void ForceGC();

};
