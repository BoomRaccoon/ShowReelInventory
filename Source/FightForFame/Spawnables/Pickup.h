// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/Inventory.h"
#include "Interfaces/Interaction.h"
#include "Pickup.generated.h"


class USphereComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UTextRenderComponent;
class AFightForFameCharacter;

UCLASS()
class FIGHTFORFAME_API APickup : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float AdditionalFarInteractionRange = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta = (RowType = Item))
	FDataTableRowHandle TableRow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(EditCondition="!TableRow.IsNull()"))
	FItem Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* FarInteraction;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(BlueprintReadWrite)
	UTextRenderComponent* PickupText;

	UPROPERTY()
	AFightForFameCharacter* Character;

	FTimerHandle SetTextUpwardHandle;

private:
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void InitMesh();
public:
	void OnConstruction(const FTransform& Transform) override;
	void PostInitializeComponents() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void UpdateTextLocation();

	void Interact_Implementation(AFightForFameCharacter* Char) override;

};
