// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightForFameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyCharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
#include "../Components/AC_InventoryManager.h"
#include "../Pickup.h"
#include "../Interfaces/Interaction.h"


//////////////////////////////////////////////////////////////////////////
// AFightForFameCharacter

AFightForFameCharacter::AFightForFameCharacter()
{
	
}

AFightForFameCharacter::AFightForFameCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InventoryManager = CreateDefaultSubobject<UAC_InventoryManager>("InventoryManager");

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");

	Char_ASC = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	Char_ASC->SetIsReplicated(true);
	Char_ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	

	BaseAttributes = CreateDefaultSubobject<UBasicAttributes>("Base Attributeset");
	
	/*
		EQUIPMENT MESHES
	*/

	Helmet = CreateDefaultSubobject<UStaticMeshComponent>("Helmet");
	Neckless = CreateDefaultSubobject<UStaticMeshComponent>("Neckless");
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Hand1 = CreateDefaultSubobject<UStaticMeshComponent>("Hand1");
	Hand2 = CreateDefaultSubobject<UStaticMeshComponent>("Hand2");
	Pants = CreateDefaultSubobject<UStaticMeshComponent>("Pants");
	Shoes = CreateDefaultSubobject<UStaticMeshComponent>("Shoes");
	Helmet->SetupAttachment(GetMesh());
	Neckless->SetupAttachment(GetMesh());
	Body->SetupAttachment(GetMesh());
	Hand1->SetupAttachment(GetMesh(), "s_hand_r");
	Hand2->SetupAttachment(GetMesh(), "s_hand_l");
	Pants->SetupAttachment(GetMesh());
	Shoes->SetupAttachment(GetMesh());
	//////////////////////////////////////////////


	
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

}

void AFightForFameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFightForFameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// ACTION SETUP
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// JUMPING
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// MOVEMENT and LOOKING
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFightForFameCharacter::Move);		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFightForFameCharacter::Look);

		// INTERACT
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AFightForFameCharacter::Interact);



	}
}

void AFightForFameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (!GetMyMovementComponent()->GetIsClimbing())
		{

			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
		else
		{
			//GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			AddMovementInput(GetActorUpVector(), MovementVector.Y);
		}
		/*else
		{
			GetCharacterMovement()->GravityScale = 0;
			AddMovementInput(GetActorUpVector(), MovementVector.Y);
		}*/
	}
}

void AFightForFameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFightForFameCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Char_ASC->InitAbilityActorInfo(this, this);
}
	
void AFightForFameCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	Char_ASC->InitAbilityActorInfo(this, this);
}

void AFightForFameCharacter::Interact()
{
	FHitResult OutHit;
	bool hit = GetWorld()->LineTraceSingleByChannel(OutHit, FollowCamera->GetComponentLocation(), FollowCamera->GetComponentLocation() + (FollowCamera->GetForwardVector()*1000), ECollisionChannel::ECC_GameTraceChannel10);
	if (hit)
	{
		if(OutHit.GetActor()->Implements<UInteraction>())
		{
			IInteraction::Execute_Interact(OutHit.GetActor(), this);
		}
	}
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s"), *OutHit.GetActor()->GetActorNameOrLabel()));
		
	DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation(), FollowCamera->GetComponentLocation() + (FollowCamera->GetForwardVector() * 1000), FColor::Cyan, false, 5.0f, 0, 5.0f);
}

UMyCharacterMovementComponent* AFightForFameCharacter::GetMyMovementComponent() const
{
	return static_cast<UMyCharacterMovementComponent*>(GetCharacterMovement());
}