// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_HitDetection_Box.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackBoxHitSingle, const FHitResult&, HitResult);

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UAbilityTask_HitDetection_Box : public UAbilityTask
{
	GENERATED_BODY()

	UAbilityTask_HitDetection_Box();

	UPROPERTY(BlueprintAssignable)
	FOnAttackBoxHitSingle SingleHitActor;


	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "BeginAttackTrace(Box)", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_HitDetection_Box* BeginBoxTrace(UGameplayAbility* OwningAbility, FName StartSocket, FName EndSocket);

	FName m_StartSocket;
	FName m_EndSocket;

	FHitResult OutHit;
	FHitResult OutHitDebug;

	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;

public:
	TArray<AActor*> HitActors;
	int count;

	void TickTask(float DeltaTime) override;


protected:
	void OnGameplayTaskInitialized(UGameplayTask& Task) override;
	UFUNCTION()
	void EndAttackCollision(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	void Activate() override;
	
};
