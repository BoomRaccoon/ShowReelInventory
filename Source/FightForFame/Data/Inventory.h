// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "Inventory.generated.h"


UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Armor UMETA(DisplayName="Armor"),
	W1 UMETA(DisplayName = "W1"), 
	W2 UMETA(DisplayName = "W2"),
	Consumeable UMETA(DisplayName = "Consumeable"),
	Misc UMETA(DisplayName = "Misc")
};

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	s_Head = 0,
	s_Neckless,
	s_Body,
	s_Hand1,
	s_Hand2,
	s_Pants,
	s_Shoes
};


UENUM(BlueprintType, Meta = (Bitflags))
enum class EInteractActions : uint8
{
	None = 0 UMETA(Hidden),
	Useable = 1 UMETA(DisplayName="Use"),
	Equippable = 2 UMETA(DisplayName = "Equip"),
	Consumeable = 4 UMETA(DisplayName = "Consume"),
	Enhanceable = 8 UMETA(DisplayName = "Enhance"),

};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Armor = 0,
	Weapon,
	Misc	
};

USTRUCT(BlueprintType)
struct FItem : public FTableRowBase
{
	GENERATED_BODY()
	
	FItem() = default;	

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Durability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FIntPoint SlotSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UAnimMontage>> AttackAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EInteractionActions"))
	uint8 Interactions;

};


FORCEINLINE uint32 GetTypeHash(const FItem& Item)
{
	uint32 Hash = FCrc::MemCrc32(&Item, sizeof(FItem));
	return Hash;
}