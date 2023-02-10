// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Base/FightForFameCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Item Mesh");
	ItemMesh->SetSimulatePhysics(true);
	
	FarInteraction = CreateDefaultSubobject<USphereComponent>("Interaction (Far)");
	CloseInteraction = CreateDefaultSubobject<UBoxComponent>("Interaction (Close)");
	PickupText = CreateDefaultSubobject<UTextRenderComponent>("PickupText");

	FarInteraction->SetupAttachment(ItemMesh);
	CloseInteraction->SetupAttachment(ItemMesh);

	PickupText->SetVisibility(false);
	SetActorTickEnabled(false);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	FarInteraction->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
	FarInteraction->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Character)
		PickupText->SetWorldRotation(FRotationMatrix::MakeFromX(Character->FollowCamera->GetComponentLocation() - GetActorLocation()).Rotator());
}

void APickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!TableRow.IsNull() && !TableRow.RowName.IsNone())
	{
		Item = TableRow.GetRow<FItem>(TableRow.DataTable->GetName());
		if (ItemMesh->SetStaticMesh(Item.Mesh.LoadSynchronous()))
		{			
			FBoxSphereBounds ItemBounds = ItemMesh->GetStaticMesh()->GetBounds();
			FarInteraction->SetSphereRadius(ItemBounds.SphereRadius + AdditionalFarInteractionRange);
			FarInteraction->SetRelativeLocation(ItemBounds.Origin);
			CloseInteraction->SetBoxExtent(ItemBounds.BoxExtent);
			CloseInteraction->SetRelativeLocation(ItemBounds.Origin);

			if (!TableRow.RowName.IsNone())
			{
				PickupText->SetText(FText::FromName(TableRow.RowName));
			}
		}
	}
}

void APickup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Character = Cast<AFightForFameCharacter>(OtherActor);
	if (Character)
	{
		SetActorTickEnabled(true);
		GetWorldTimerManager().SetTimer(SetTextUpwardHandle, this, &APickup::UpdateTextLocation, 0.2f);
		PickupText->SetVisibility(true);
	}
}

void APickup::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetActorTickEnabled(false);
	GetWorldTimerManager().ClearTimer(SetTextUpwardHandle);
	PickupText->SetVisibility(false);
}

void APickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(Item.Mesh)
		ItemMesh->SetStaticMesh(Item.Mesh.Get());	
}

void APickup::UpdateTextLocation()
{
	PickupText->SetWorldLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + FarInteraction->GetScaledSphereRadius()));
}