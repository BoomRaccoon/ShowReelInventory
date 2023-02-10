// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/AbilityTask_HitDetection_Sphere.h"
#include <../Private/KismetTraceUtils.h>


UAbilityTask_HitDetection_Sphere::UAbilityTask_HitDetection_Sphere()
{

}

UAbilityTask_HitDetection_Sphere* UAbilityTask_HitDetection_Sphere::BeginSphereTrace(UGameplayAbility* OwningAbility, FName InStartSocket, FName InEndSocket, float InSphereRadius)
{
	UAbilityTask_HitDetection_Sphere* MyObj = NewAbilityTask<UAbilityTask_HitDetection_Sphere>(OwningAbility);
	MyObj->StartSocket = InStartSocket;
	MyObj->EndSocket = InEndSocket;
	MyObj->SphereRadius = InSphereRadius;

	return MyObj;
}

void UAbilityTask_HitDetection_Sphere::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	FVector StartTraceLocation = Ability->GetActorInfo().SkeletalMeshComponent->GetSocketLocation(StartSocket);
	FVector EndTraceLocation = Ability->GetActorInfo().SkeletalMeshComponent->GetSocketLocation(EndSocket);
	Params.AddIgnoredActor(Ability->GetActorInfo().AvatarActor.Get());
	UWorld* World = GetWorld();

	bool const bHit = World ? World->SweepSingleByObjectType(OutHit, StartTraceLocation, EndTraceLocation, FRotator(0, 0, 0).Quaternion(), ObjectParams, FCollisionShape::MakeSphere(SphereRadius), Params) : false;
#if UE_BUILD_DEBUG || UE_EDITOR
	DrawDebugSphereTraceSingle(World, StartTraceLocation, EndTraceLocation, SphereRadius, EDrawDebugTrace::Persistent, true, OutHitDebug, FLinearColor::Red, FLinearColor::Green, 2.0f);
#endif

	if (bHit)
	{
		Params.AddIgnoredActor(OutHit.GetActor());
		//HitActors.AddUnique(OutHit.GetActor());
		SingleHitActor.Broadcast(OutHit);
	}
}

void UAbilityTask_HitDetection_Sphere::OnGameplayTaskInitialized(UGameplayTask& Task)
{

}

void UAbilityTask_HitDetection_Sphere::EndAttackCollision(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{

}

void UAbilityTask_HitDetection_Sphere::Activate()
{
	Super::Activate();
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	Params.AddIgnoredActor(Ability->GetActorInfo().AvatarActor.Get());
	Ability->GetActorInfo().SkeletalMeshComponent->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::EndAttackCollision);
}
