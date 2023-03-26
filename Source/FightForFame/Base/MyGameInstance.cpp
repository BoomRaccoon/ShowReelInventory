// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include <Framework/Application/SlateApplication.h>
#include <Framework/Application/NavigationConfig.h>
#include <JsonObjectConverter.h>
#include "Base/FightForFameCharacter.h"




void UMyGameInstance::Init()
{
	Super::Init();


}

void UMyGameInstance::SaveGame()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	AFightForFameCharacter* PlayerChar = Cast<AFightForFameCharacter>(Player->GetPawn());


	FString Out;
	FString Path = FPaths::GameSourceDir();
	Path.Append("TestJson.json");
	
	//FJsonObjectConverter::UStructToJsonObjectString(Stats, Out, 0, 0);
	//FFileHelper::SaveStringToFile(Out, *Path);
}

void UMyGameInstance::LoadGame()
{
	FString Loaded;
	
}
