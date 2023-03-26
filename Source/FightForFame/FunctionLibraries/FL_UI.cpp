// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/FL_UI.h"
#include "Base/FightForFameCharacter.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h>

FDateTime UFL_UI::GetFileModificationTime(FString Path)
{
	FDateTime Date = IFileManager::Get().GetTimeStamp(*Path);
	return Date;
}

void UFL_UI::WritePlayerMappableKeys(AFightForFameCharacter* Player)
{
	/*if (Player->IsPlayerControlled())
	{
		APlayerController* PC = Cast<APlayerController>(Player->GetController());

		UEnhancedPlayerInput* EPI = Cast<UEnhancedPlayerInput>(PC->PlayerInput);
		if (EPI)
		{
			const TArray<FEnhancedActionKeyMapping>& MappingsArray = EPI->GetEnhancedActionMappings();
			for (const FEnhancedActionKeyMapping& Mapping : MappingsArray)
			{

			}
		}
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddPlayerMappedKey()
	}*/

}

void UFL_UI::ForceGC()
{
	GEngine->ForceGarbageCollection(true);
}

