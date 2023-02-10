// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPawn.h"
#include "AbilitySystemComponent.h"
#include "../GAS/Attributes/BasicAttributes.h"
#include <AIModule/Classes/Perception/AIPerceptionComponent.h>
#include <GameFramework/PawnMovementComponent.h>



// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Navi = CreateDefaultSubobject<UPawnMovementComponent>("Navigation Movement");

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attriutes = CreateDefaultSubobject<UBasicAttributes>("Attribute Set");

}

void AAIPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ASC->InitAbilityActorInfo(this, this);
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

