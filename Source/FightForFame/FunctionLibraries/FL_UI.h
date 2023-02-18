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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Interface Helper", meta=(Keywords="uniform grid column"))
	static int32 GetNumberOfColumns(UUniformGridPanel* UniformGridPanel);
};
