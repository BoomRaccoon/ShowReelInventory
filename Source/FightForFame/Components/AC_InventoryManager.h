// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Data/Inventory.h"
#include "AC_InventoryManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Inventory, Log, All);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTFORFAME_API UAC_InventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TMap<int, FItem > OwnedItems;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TMap<EEquipmentSlot, FItem> EquippedItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TMap<int, bool> InventorySlots;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	FVector2D ColumnsRows {7,7};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	int InventorySize = 63;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UUserWidget* InventoryWidget;
	
	/*
		Possible setup for bit field
	*/
	//int32 BitMask = 0;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<int32> SlotStates {0, 0, 0, 0, 0, 0, 0, 0};*/


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	// Sets default values for this component's properties
	UAC_InventoryManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(int InventorySlot, FItem Item);

	void CreateBitMask(FItem& Item, int InventorySlot);
	UFUNCTION(BlueprintCallable)
	void EquipItem(EEquipmentSlot Slot, FItem Item);

	/*
	Returns true if the item fits at the specified slot
	@param Size := Size.X=Columns  Size.Y=Rows
	@param Slot := position of the item in the inventory
	*/
	bool CheckSpace(FVector2D Size, int Slot);


		
public:
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
