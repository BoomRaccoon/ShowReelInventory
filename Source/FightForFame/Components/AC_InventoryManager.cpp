// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_InventoryManager.h"
#include "../Base/FightForFameCharacter.h"


DEFINE_LOG_CATEGORY(Inventory);


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
	InventorySlots.SetNum((ColumnsRows.X+1) * (ColumnsRows.Y+1)); // Init inventory array of slot states
	InventorySize = (ColumnsRows.X + 1) * (ColumnsRows.Y + 1) -1;
	OwnedItems.Init(FItem(), (ColumnsRows.X + 1) * (ColumnsRows.Y + 1));
	EquippedItems.Init(FItem(), 7);
	// ...
	
}


// Called every frame
void UAC_InventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UAC_InventoryManager::AddItem(int InventorySlot, const FItem& Item)
{
	if (InventorySlot < InventorySize)
	{
		if(!CheckSpace(Item.SlotSize, InventorySlot))
			return false;
		CommitChange(Item.SlotSize, InventorySlot);
		OwnedItems[InventorySlot] = Item;
		return true;
	}
	return false;
}


bool UAC_InventoryManager::EquipItem(EEquipmentSlot Slot, const FItem& Item, int InventorySlot)
{
	/*
	s_Head = 0,
	s_Neckless,
	s_Body,
	s_Hand1,
	s_Hand2,
	s_Pants,
	s_Shoes
	*/
	
	if (EquippedItems[(int)Slot].Name.IsEmpty())
	{
		AFightForFameCharacter* Player = Cast<AFightForFameCharacter>(GetOwner());
		if (Player)
		{
			EquippedItems[(int)Slot] = Item;
			switch (Slot)
			{
					case 0:
						Player->Helmet->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					case 1:
						Player->Neckless->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					case 2:
						Player->Body->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					case 3:
						Player->Hand1->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					case 4:
						Player->Hand2->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					case 5:
						Player->Pants->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					case 6:
						Player->Shoes->SetStaticMesh(Item.Mesh.LoadSynchronous());
						break;
					default:
						break;
			}
			if(InventorySlot != -1)
				RemoveItem(Item, InventorySlot);

			return true;
		}
	}
	return false;
}

bool UAC_InventoryManager::CheckSpace(FIntPoint ItemSize, int Slot, int PreviousSlot)
{
	// early out when item goes beyond maximum rows/columns
	if (! ((Slot%(ColumnsRows.X + 1))+ ItemSize.X <= ColumnsRows.X+1 && FMath::Floor(Slot/(ColumnsRows.Y+1)) + ItemSize.Y <= ColumnsRows.Y+1) )
	{
		UE_LOG(Inventory, Log, TEXT("Item exceeds inventory bounds -> doesn't fit"));
		return false;
	}

	TArray<bool> tempSlots = InventorySlots;
	if (! (PreviousSlot < 0) )
	{
		// temporary array to set slots of previous false before the check check space if item is occupying slots
		for (int i = PreviousSlot; i < PreviousSlot+ (ColumnsRows.X+1) * (ItemSize.Y-1)+1; i = i + ColumnsRows.Y + 1)
		{
			for (int j = 0; j < ItemSize.X; j++)
			{
				tempSlots[i + j] = false;
			}
		}
	}


	// check every affected slot state, return if a slot is occupied
	for (int i = Slot; i < Slot+(ColumnsRows.Y+1)*(ItemSize.Y-1) + (ItemSize.X-1); i= i+ColumnsRows.Y+1)
	{
		for (int j = 0; j < ItemSize.X; j++)
		{ 
			if(tempSlots[i + j])
			{
				//UE_LOG(Inventory, Log, TEXT("Item did not fit"));
				return false;
			}
		}
	}
	return true;
}


int UAC_InventoryManager::FindSlot(const FItem& Item)
{
	int lastAvailableIndex = InventorySize - ( (Item.SlotSize.Y-1) * ColumnsRows.X) - ColumnsRows.Y;
	
	for(int Slot = 0; Slot < lastAvailableIndex; Slot++)
	{
		if (CheckSpace(Item.SlotSize, Slot))
			return Slot;
	}
	
	return -1;
}

void UAC_InventoryManager::CommitChange(FIntPoint Size, int Slot)
{
	for (int i = Slot; i < Slot+ (ColumnsRows.X+1) * Size.Y; i= i + ColumnsRows.Y + 1)
	{
		for (int j = 0; j < Size.X; j++)
		{
			InventorySlots[i + j] = true;
		}
	}
}

void UAC_InventoryManager::RemoveItem(FItem Item, int Slot)
{
	if (! (Slot < 0))
	{
		for (int i = Slot; i < Slot + ColumnsRows.X * Item.SlotSize.Y + 1; i = i + ColumnsRows.Y + 1)
		{
			for (int j = 0; j < Item.SlotSize.Y; j++)
			{
				InventorySlots[i + j] = false;
			}
		}
		OwnedItems[Slot] = FItem();
	}
	else
	{
		EquippedItems[(int)Item.EquipmentSlot] = FItem();
		UnequipItem(Item);
	}
}

bool UAC_InventoryManager::MoveItem(FItem& Item, int Slot, int PreviousSlot, bool WasEquipped)
{
	if (!CheckSpace(Item.SlotSize, Slot, PreviousSlot))
	{
		UE_LOG(Inventory, Log, TEXT("Item did not fit"));
		return false;
	}

	if (!(PreviousSlot < 0))
	{
		for (int i = PreviousSlot; i < PreviousSlot + ColumnsRows.X * Item.SlotSize.Y + 1; i = i + ColumnsRows.Y + 1)
		{
			for (int j = 0; j < Item.SlotSize.X; j++)
			{
				InventorySlots[i + j] = false;
			}
		}
	}
	else if (WasEquipped)
	{
		UnequipItem(Item);
	}

	CommitChange(Item.SlotSize, Slot);

	if (!(PreviousSlot < 0))
		OwnedItems[PreviousSlot] = FItem();
	OwnedItems[Slot] = Item;

	return true;
}

void UAC_InventoryManager::UnequipItem(const FItem& Item)
{
	AFightForFameCharacter* Player = Cast<AFightForFameCharacter>(GetOwner());
	EquippedItems[(int)Item.EquipmentSlot] = FItem();
	switch (Item.EquipmentSlot)
	{
	case 0:
		Player->Helmet->SetStaticMesh(nullptr);
		break;
	case 1:
		Player->Neckless->SetStaticMesh(nullptr);
		break;
	case 2:
		Player->Body->SetStaticMesh(nullptr); 
		break;
	case 3:
		Player->Hand1->SetStaticMesh(nullptr);
		break;
	case 4:
		Player->Hand2->SetStaticMesh(nullptr);
		break;
	case 5:
		Player->Pants->SetStaticMesh(nullptr);
		break;
	case 6:
		Player->Shoes->SetStaticMesh(nullptr);
		break;
	default:
		break;
	}
}


void UAC_InventoryManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UE_LOG(Inventory, Log, TEXT("ChangedPropertyName: %s"), *PropertyChangedEvent.Property->GetName());
	
}


