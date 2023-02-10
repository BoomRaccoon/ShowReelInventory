// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/CustomGameInstance.h"
#include <Framework/Application/SlateApplication.h>
#include "Framework/Application/NavigationConfig.h"

UCustomGameInstance::UCustomGameInstance()
{
	
}

void UCustomGameInstance::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Add(EKeys::W, EUINavigation::Up);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Add(EKeys::A, EUINavigation::Left);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Add(EKeys::S, EUINavigation::Down);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Add(EKeys::D, EUINavigation::Right);
}
