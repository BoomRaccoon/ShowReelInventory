// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_HitDetection_Sphere.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackSphereHitSingle, const FHitResult&, HitResult);

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UAbilityTask_HitDetection_Sphere : public UAbilityTask
{
	GENERATED_BODY()

	UAbilityTask_HitDetection_Sphere();

	UPROPERTY(BlueprintAssignable)
	FOnAttackSphereHitSingle SingleHitActor;


	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "BeginAttackTrace(Sphere)", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_HitDetection_Sphere* BeginSphereTrace(UGameplayAbility* OwningAbility, FName InStartSocket, FName InEndSocket, float InSphereRadius);

	FName StartSocket;
	FName EndSocket;

	float SphereRadius;

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
