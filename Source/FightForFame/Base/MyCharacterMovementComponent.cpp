// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MyCharacterMovementComponent.h"
#include <Stats/Stats2.h>
#include "GameFramework/Character.h"
#include <GameFramework/CharacterMovementComponent.h>

#define MMode(MovementMode) (uint8)ECustom_Movement_Mode::##MovementMode

void UMyCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	//Super::PhysCustom(deltaTime, Iterations);

	if (CustomMovementMode == MMode(MOVE_Climbing))
	{
		if (deltaTime < MIN_TICK_TIME)
		{
			return;
		}

		RestorePreAdditiveRootMotionVelocity();

		if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
		{
			CalcVelocity(deltaTime, 100, true, GetMaxBrakingDeceleration());
		}

		ApplyRootMotionToVelocity(deltaTime);

		Iterations++;
		bJustTeleported = false;

		FVector OldLocation = UpdatedComponent->GetComponentLocation();
		const FVector Adjusted = Velocity * deltaTime;
		FHitResult Hit(1.f);
		SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);

		if (Hit.Time < 1.f)
		{
			const FVector GravDir = FVector(0.f, 0.f, -1.f);
			const FVector VelDir = Velocity.GetSafeNormal();
			const float UpDown = GravDir | VelDir;

			bool bSteppedUp = false;
			/*if ((FMath::Abs(Hit.ImpactNormal.Z) < 0.2f) && (UpDown < 0.5f) && (UpDown > -0.2f) && CanStepUp(Hit))
			{
				float stepZ = UpdatedComponent->GetComponentLocation().Z;
				bSteppedUp = StepUp(GravDir, Adjusted * (1.f - Hit.Time), Hit);
				if (bSteppedUp)
				{
					OldLocation.Z = UpdatedComponent->GetComponentLocation().Z + (OldLocation.Z - stepZ);
				}
			}*/

			if (!bSteppedUp)
			{
				//adjust and try again
				HandleImpact(Hit, deltaTime, Adjusted);
				SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
			}
		}

		//if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
		//{
		//		 (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
		//}
	}
}

bool UMyCharacterMovementComponent::GetIsClimbing()
{
	bool Climbo = (CustomMovementMode == MMode(MOVE_Climbing));	
	return (CustomMovementMode == MMode(MOVE_Climbing));
}


void UMyCharacterMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
	if(CustomMovementMode == 0)
		Super::PhysWalking(deltaTime, Iterations);	
}

