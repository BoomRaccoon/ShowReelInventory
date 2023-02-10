// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/AttackCollisionDetection.h"

UAttackCollisionDetection::UAttackCollisionDetection()
{

}

UAttackCollisionDetection*  UAttackCollisionDetection::UAttackCollisionDetection::BeginBoxTrace(UGameplayAbility* OwningAbility, FName StartSocket, FName EndSocket)
{
	UAttackCollisionDetection* MyObj = NewAbilityTask<UAttackCollisionDetection>(OwningAbility);
	MyObj->m_StartSocket = StartSocket;
	MyObj->m_EndSocket = EndSocket;

	return MyObj;
}

void UAttackCollisionDetection::TickTask(float DeltaTime)
{

}

void UAttackCollisionDetection::OnGameplayTaskInitialized(UGameplayTask& Task)
{

}



void UAttackCollisionDetection::EndAttackCollision(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{

}



void UAttackCollisionDetection::Activate()
{

}

