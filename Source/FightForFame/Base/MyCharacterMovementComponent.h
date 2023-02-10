// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.generated.h"

UENUM()
enum class ECustom_Movement_Mode : uint8
{
	MOVE_Climbing = 1
};

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsClimbing();
	
protected:
	void PhysCustom(float deltaTime, int32 Iterations) override;

	void PhysWalking(float deltaTime, int32 Iterations) override;

};
