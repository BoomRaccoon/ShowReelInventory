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

	// ...
	
}


// Called every frame
void UAC_InventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_InventoryManager::AddItem(int InventorySlot, FItem Item)
{
	if (InventorySlot < InventorySize)
	{
		if(!CheckSpace(Item.SlotSize, InventorySlot))
			return;
		OwnedItems.Emplace(InventorySlot, Item);
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
			
	}
}

bool UAC_InventoryManager::CheckSpace(FVector2D Size, int Slot)
{
	// early out when item breaches maximum rows/columns
	if (!Slot + Size.X < ColumnsRows.X && Slot + Size.Y < ColumnsRows.Y)
	{
		UE_LOG(Inventory, Log, TEXT("Item exceeds inventory bounds -> doesn't fit"));
		return false;
	}

	// check every slot state, out if a slot is occupied
	for (int i = 0; i < Size.Y; i++)
	{
		for (int j = 0; j < Size.X; j++)
		{
			if(InventorySlots.Find(Slot+i*8+j))
			{
				UE_LOG(Inventory, Log, TEXT("Item did not fit"));
				return false;
			}
		}
	}

	return true;
}

void UAC_InventoryManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UE_LOG(Inventory, Log, TEXT("ChangedPropertyName: %s"), *PropertyChangedEvent.Property->GetName());
	
}


