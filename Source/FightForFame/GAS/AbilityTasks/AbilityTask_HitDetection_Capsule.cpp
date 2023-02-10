// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/AbilityTask_HitDetection_Capsule.h"
#include <../Private/KismetTraceUtils.h>


UAbilityTask_HitDetection_Capsule::UAbilityTask_HitDetection_Capsule()
{
	
}

UAbilityTask_HitDetection_Capsule* UAbilityTask_HitDetection_Capsule::BeginSphereTrace(UGameplayAbility* OwningAbility, FName StartSocket, FName EndSocket)
{
	UAbilityTask_HitDetection_Capsule* MyObj = NewAbilityTask<UAbilityTask_HitDetection_Capsule>(OwningAbility);
	MyObj->m_StartSocket = StartSocket;
	MyObj->m_EndSocket = EndSocket;

	return MyObj;
}

void UAbilityTask_HitDetection_Capsule::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	FVector StartTraceLocation = Ability->GetActorInfo().SkeletalMeshComponent->GetSocketLocation(m_StartSocket);
	FVector EndTraceLocation = Ability->GetActorInfo().SkeletalMeshComponent->GetSocketLocation(m_EndSocket);
	Params.AddIgnoredActor(Ability->GetActorInfo().AvatarActor.Get());
	UWorld* World = GetWorld();
	bool const bHit = World ? World->SweepSingleByObjectType(OutHit, StartTraceLocation, EndTraceLocation, FRotator(0, 0, 0).Quaternion(), ObjectParams, FCollisionShape(), Params) : false;
#if UE_BUILD_DEBUG || UE_EDITOR
	DrawDebugLineTraceSingle(World, StartTraceLocation, EndTraceLocation, EDrawDebugTrace::Persistent, true, OutHitDebug, FLinearColor::Red, FLinearColor::Green, 2.0f);
#endif

	if (bHit)
	{
		Params.AddIgnoredActor(OutHit.GetActor());
		//HitActors.AddUnique(OutHit.GetActor());
		SingleHitActor.Broadcast(OutHit);
	}
}

void UAbilityTask_HitDetection_Capsule::OnGameplayTaskInitialized(UGameplayTask& Task)
{

}

void UAbilityTask_HitDetection_Capsule::EndAttackCollision(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{

}

void UAbilityTask_HitDetection_Capsule::Activate()
{
	Super::Activate();
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	Params.AddIgnoredActor(Ability->GetActorInfo().AvatarActor.Get());
	Ability->GetActorInfo().SkeletalMeshComponent->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::EndAttackCollision);
}
