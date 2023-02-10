// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

class UAbilitySystemComponent;
class UBasicAttributes;
class UAIPerceptionComponent;
class UPawnMovementComponent;


UCLASS()
class FIGHTFORFAME_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

	void PossessedBy(AController* NewController);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

 
	UPROPERTY(EditDefaultsOnly)
	UPawnMovementComponent* Navi;

	UPROPERTY()
	UBasicAttributes* Attriutes;

	UPROPERTY()	
	UAbilitySystemComponent* ASC;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
