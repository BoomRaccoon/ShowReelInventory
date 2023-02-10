// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/Interaction.h"
#include <AbilitySystemComponent.h>
#include "GAS/Attributes/BasicAttributes.h"
#include "FightForFameCharacter.generated.h"


class UBasicAttributes;
class UMyCharacterMovementComponent;
class UMotionWarpingComponent;
class UAC_InventoryManager;

UCLASS(config=Game)
class AFightForFameCharacter : public ACharacter
{
	GENERATED_BODY()

	///////////////////////////////////////////// INPUT PROPERTIES
	/** MAPPINGCONTEXT */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// INPUT ACTIONS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Interact;
	////////////////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionRange;

	UBasicAttributes* BaseAttributes;
	UAbilitySystemComponent* Char_ASC;

public:
	///////////////////////////////////////////// CAMERA SETUP
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	/////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAC_InventoryManager* InventoryManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMotionWarpingComponent* MotionWarping;
	
	/*
		EQUIPMENT MESHES
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Helmet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Neckless;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Hand1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Hand2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pants;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Shoes;
	//////////////////////////////////////////////

	AFightForFameCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	AFightForFameCharacter();
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	void Interact();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UMyCharacterMovementComponent* GetMyMovementComponent() const;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

