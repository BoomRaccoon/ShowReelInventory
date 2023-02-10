// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributes.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class FIGHTFORFAME_API UBasicAttributes : public UAttributeSet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health, meta=(AllowPrivateAccess = "true"))
	FGameplayAttributeData Health = 100;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, Health);
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing=OnRep_Stamina, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Stamina = 100;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, Stamina);
	
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, Category = "lvl", ReplicatedUsing=OnRep_lvl, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData lvl = 1;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, lvl);
	
	UFUNCTION()
	virtual void OnRep_lvl(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttack", ReplicatedUsing=OnRep_BaseAttack, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BaseAttack = 5;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, BaseAttack);
	
	UFUNCTION()
	virtual void OnRep_BaseAttack(const FGameplayAttributeData& OldValue);
	
	
public:
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
