// Fill out your copyright notice in the Description page of Project Settings.


#include "SamAttributeSet.h"
#include "Net/UnrealNetwork.h"

// Constructor to initialize default values
USamAttributeSet::USamAttributeSet()
{
	// Initial values for Health
	Health = 100.f;
	MaxHealth = 100.f;
	HealthRegen = 5.f;
	DefaultHealthRegen = 5.f;

	// Initial values for stamina
	Stamina = 100.f;
	MaxStamina = 100.f;
	StaminaRegen = 10.f;
	DefaultStaminaRegen = 10.f;

	// Initial values for stagger
	Stagger = 10.f;
	MaxStagger = 10.f;
	StaggerMult = 1.0f;

	// Initial values for armor
	Armor = 10.f;
	DefaultArmor = 10.f;
}

// Replication notification functions
void USamAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, Health, OldHealth);
}

void USamAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, MaxHealth, OldMaxHealth);
}

void USamAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, HealthRegen, OldHealthRegen);
}

void USamAttributeSet::OnRep_DefaultHealthRegen(const FGameplayAttributeData& OldDefaultHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, DefaultHealthRegen, OldDefaultHealthRegen);
}

void USamAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, Stamina, OldStamina);
}

void USamAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, MaxStamina, OldMaxStamina);
}

void USamAttributeSet::OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, StaminaRegen, OldStaminaRegen);
}

void USamAttributeSet::OnRep_DefaultStaminaRegen(const FGameplayAttributeData& OldDefaultStaminaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, DefaultStaminaRegen, OldDefaultStaminaRegen);
}

void USamAttributeSet::OnRep_Stagger(const FGameplayAttributeData& OldStagger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, Stagger, OldStagger);
}

void USamAttributeSet::OnRep_MaxStagger(const FGameplayAttributeData& OldMaxStagger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, MaxStagger, OldMaxStagger);
}

void USamAttributeSet::OnRep_StaggerMult(const FGameplayAttributeData& OldStaggerMult)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, StaggerMult, OldStaggerMult);
}

void USamAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, Armor, OldArmor);
}

void USamAttributeSet::OnRep_DefaultArmor(const FGameplayAttributeData& OldDefaultArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USamAttributeSet, DefaultArmor, OldDefaultArmor);
}

// Replication logic to replicate all attributes
void USamAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate attributes
	DOREPLIFETIME(USamAttributeSet, Health);
	DOREPLIFETIME(USamAttributeSet, MaxHealth);
	DOREPLIFETIME(USamAttributeSet, HealthRegen);
	DOREPLIFETIME(USamAttributeSet, DefaultHealthRegen);
	DOREPLIFETIME(USamAttributeSet, Stamina);
	DOREPLIFETIME(USamAttributeSet, MaxStamina);
	DOREPLIFETIME(USamAttributeSet, StaminaRegen);
	DOREPLIFETIME(USamAttributeSet, DefaultStaminaRegen);
	DOREPLIFETIME(USamAttributeSet, Stagger);
	DOREPLIFETIME(USamAttributeSet, MaxStagger);
	DOREPLIFETIME(USamAttributeSet, StaggerMult);
	DOREPLIFETIME(USamAttributeSet, Armor);
	DOREPLIFETIME(USamAttributeSet, DefaultArmor);
}