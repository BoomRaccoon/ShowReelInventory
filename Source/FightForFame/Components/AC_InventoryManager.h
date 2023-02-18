// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Data/Inventory.h"
#include "AC_InventoryManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTFORFAME_API UAC_InventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TMap<FItem, int> OwnedItems;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TMap<EEquipmentSlot, FItem> EquippedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 rows = 8;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 columns = 8;
	
	int32 BitMask = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<int32> SlotStates {0, 0, 0, 0, 0, 0, 0, 0};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UUserWidget* InventoryWidget;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	// Sets default values for this component's properties
	UAC_InventoryManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(FItem Item, int InventorySlot);

	void CreateBitMask(FItem& Item, int InventorySlot);
	UFUNCTION(BlueprintCallable)
	void EquipItem(EEquipmentSlot Slot, FItem Item);


		
public:
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
