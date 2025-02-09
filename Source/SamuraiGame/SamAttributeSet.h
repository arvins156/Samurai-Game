// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SamAttributeSet.generated.h"

/**
 * 
 */
// Macros to mark properties for replication
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class SAMURAIGAME_API USamAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USamAttributeSet();

	// Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, Health)

	// Max Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, MaxHealth)

	// Health Regen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, HealthRegen)

	// Default Health Regen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefaultHealthRegen)
	FGameplayAttributeData DefaultHealthRegen;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, DefaultHealthRegen)

	// Stamina
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, Stamina)

	// Max Stamina
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, MaxStamina)

	// Stamina Regen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_StaminaRegen)
	FGameplayAttributeData StaminaRegen;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, StaminaRegen)

	// Default Stamina Regen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefaultStaminaRegen)
	FGameplayAttributeData DefaultStaminaRegen;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, DefaultStaminaRegen)

	// Stagger
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stagger)
	FGameplayAttributeData Stagger;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, Stagger)

	// Max Stagger
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStagger)
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, MaxStagger)

	// Stagger Mult
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_StaggerMult)
	FGameplayAttributeData StaggerMult;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, StaggerMult)

	// Armor
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, Armor)

	// Default Armor
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefaultArmor)
	FGameplayAttributeData DefaultArmor;
	ATTRIBUTE_ACCESSORS(USamAttributeSet, DefaultArmor)

protected:

	// Replication Notification Functions for Attributes
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen);
	
	UFUNCTION()
	virtual void OnRep_DefaultHealthRegen(const FGameplayAttributeData& OldDefaultHealthRegen);
	
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	
	UFUNCTION()
	virtual void OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen);
	
	UFUNCTION()
	virtual void OnRep_DefaultStaminaRegen(const FGameplayAttributeData& OldDefaultStaminaRegen);
	
	UFUNCTION()
	virtual void OnRep_Stagger(const FGameplayAttributeData& OldStagger);
	
	UFUNCTION()
	virtual void OnRep_MaxStagger(const FGameplayAttributeData& OldMaxStagger);
	
	UFUNCTION()
	virtual void OnRep_StaggerMult(const FGameplayAttributeData& OldStaggerMult);
	
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	
	UFUNCTION()
	virtual void OnRep_DefaultArmor(const FGameplayAttributeData& OldDefaultArmor);
	
};
