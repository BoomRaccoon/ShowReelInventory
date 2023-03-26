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
	TArray<FItem> OwnedItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TArray<bool> InventorySlots; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TArray<FItem> EquippedItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	FIntPoint ColumnsRows {7,7};

	UPROPERTY()
	int InventorySize = 63;

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
	bool AddItem(int InventorySlot, const FItem& Item);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(FItem Item, int Slot);
	UFUNCTION(BlueprintCallable)
	bool MoveItem(UPARAM(ref)	 FItem& Item, int Slot, int PreviousSlot, bool WasEquqipped);


	UFUNCTION(BlueprintCallable)
	bool EquipItem(EEquipmentSlot Slot, const FItem& Item, int InventorySlot = -1);
	UFUNCTION(BlueprintCallable)
	void UnequipItem(const FItem& Item);


	/*
	Returns true if the item fits at the specified slot
	@param Size := Size.X=Columns  Size.Y=Rows
	@param Slot := position of the item in the inventory
	*/
	UFUNCTION(BlueprintCallable)
	bool CheckSpace(FIntPoint Size, int Slot, int PreviousSlot = -1);

	/* Finds a free slot for an item
	@param Item := used to get the size */
	UFUNCTION(BlueprintCallable)
	int FindSlot(const FItem& Item);
	
	/* Will set the slots to occupied
	@param Size := X=width y=height of the item
	@param Slot := top left slot index
	*/
	UFUNCTION(BlueprintCallable)
	void CommitChange(FIntPoint Size, int Slot);
	

private:
		
public:
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
