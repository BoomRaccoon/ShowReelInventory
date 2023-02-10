// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeAIController.h"

FAIRequestID AMeleeAIController::RequestMove(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr Path)
{
	Super::RequestMove(MoveRequest, Path);
	throw std::logic_error("The method or operation is not implemented.");
}
