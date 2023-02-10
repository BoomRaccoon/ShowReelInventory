// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/FL_UI.h"

FDateTime UFL_UI::GetFileModificationTime(FString Path)
{
	FDateTime Date = IFileManager::Get().GetTimeStamp(*Path);
	return Date;
}
