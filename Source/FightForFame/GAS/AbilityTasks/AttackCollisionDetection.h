// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AttackCollisionDetection.generated.h"

/* delegate that should be called after every OnHit
** and be visible as a exec pin?
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackHitSingle, const FHitResult&, HitResult);

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UAttackCollisionDetection : public UAbilityTask
{
	GENERATED_BODY()

	UAttackCollisionDetection();

	UPROPERTY(BlueprintAssignable)
	FOnAttackHitSingle HitActor;


	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "BeginAttackTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAttackCollisionDetection* BeginBoxTrace(UGameplayAbility* OwningAbility, FName StartSocket, FName EndSocket);

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
