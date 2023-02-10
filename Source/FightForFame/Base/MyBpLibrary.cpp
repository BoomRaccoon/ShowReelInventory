// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MyBpLibrary.h"

float UMyBpLibrary::GetXYDistance(const FVector Object1, const FVector Object2)
{
	return FVector::DistXY(Object1, Object2);
}