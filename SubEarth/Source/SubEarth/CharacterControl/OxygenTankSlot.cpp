// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "OxygenTankSlot.h"


/******************************************************************************/
UOxygenTankSlot::UOxygenTankSlot()
{
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_objectCollider->bHiddenInGame = false;

	m_interactableComponentType = OXYGEN_TANK_SLOT;
}

/******************************************************************************/
void UOxygenTankSlot::ExecutePrimaryAction(APickup* pickup)
{
	UE_LOG(LogTemp, Log, TEXT("UOxygenTankSlot::ExecutePrimaryAction"));
}

