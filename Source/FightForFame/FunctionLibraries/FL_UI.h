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


	UFUNCTION(BlueprintCallable, Category = "Inventory", meta = (Keywords = "inventory get occupied slots"))
	static void GetOccupiedSlots();

	UFUNCTION(BlueprintCallable, Category="UI", meta = (Keywords = "widget under cursor"))
	static void GetWidgetUnderCursor(FVector2D ScreenspacePosition);
};
