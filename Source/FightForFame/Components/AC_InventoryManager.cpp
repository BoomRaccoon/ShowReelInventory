// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_InventoryManager.h"
#include "../Base/FightForFameCharacter.h"

// Sets default values for this component's properties
UAC_InventoryManager::UAC_InventoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	// ...
}


// Called when the game starts
void UAC_InventoryManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_InventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_InventoryManager::AddItem(FItem Item, int InventorySlot)
{


	if ((InventorySlot + Item.SlotSize.X) < rows && (InventorySlot + Item.SlotSize.Y) < columns)
	{
		int32 _row = FMath::Floor(InventorySlot / rows);
		int32 _column = InventorySlot % columns;

		

		OwnedItems.Emplace(Item, InventorySlot);
	}

	//SlotStates[_row] |= (1 << n); // Take OR of i and 1 shifted n positions

}

void UAC_InventoryManager::CreateBitMask(FItem& Item ,int InventorySlot)
{
	if ((InventorySlot + Item.SlotSize.X) < rows)
	{
		for (int i = InventorySlot; i < (InventorySlot + Item.SlotSize.X); i++)
		{
			BitMask |= (1 << i); // Take OR of i and 1 shifted n positions
		}
	}
}

void UAC_InventoryManager::EquipItem(EEquipmentSlot Slot, FItem Item)
{
	EquippedItems.Emplace(Slot, Item);
	/*
	s_Head = 0,
	s_Neckless,
	s_Body,
	s_Hand1,
	s_Hand2,
	s_Pants,
	s_Shoes
	*/
	AFightForFameCharacter* Player = Cast<AFightForFameCharacter>(GetOwner());
	if (Player)
	{
		switch (Slot)
		{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					Player->Hand1->SetStaticMesh(Item.Mesh.LoadSynchronous());
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				default:
					break;
		}
			
	}
}

void UAC_InventoryManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UE_LOG(LogTemp, Log, TEXT("ChangedPropertyName: %s"), *PropertyChangedEvent.Property->GetName());
	
}


