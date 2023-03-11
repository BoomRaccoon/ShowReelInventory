// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/FL_UI.h"
#include <GenericPlatform/GenericWindow.h>
#include <Widgets/SWindow.h>
#include <Framework/Application/SlateApplication.h>

FDateTime UFL_UI::GetFileModificationTime(FString Path)
{
	FDateTime Date = IFileManager::Get().GetTimeStamp(*Path);
	return Date;
}

void UFL_UI::GetOccupiedSlots()
{
	
}

void UFL_UI::GetWidgetUnderCursor(FVector2D ScreenspacePosition)
{
	
}
