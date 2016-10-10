// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "GenericDoor.h"

/******************************************************************************/
AGenericDoor::AGenericDoor()
{
	// Setup the doorknob interactable size
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_objectCollider->bHiddenInGame = false;
	m_interactableType = GENERIC_DOOR;
	m_isLocked = true;
}

/******************************************************************************/
void AGenericDoor::ExecutePrimaryAction(APickup* pickup)
{
	if (m_isLocked)
	{
		// TODO print this out on HUD???
		UE_LOG(LogTemp, Log, TEXT("AGenericDoor::ExecutePrimaryAction  CANNOT OPEN, DOOR IS LOCKED"));
	}
	else
	{
		// TODO Animate opening the door here.
		UE_LOG(LogTemp, Log, TEXT("AGenericDoor::ExecutePrimaryAction  OPENING DOOR"));
	}
	
}

/******************************************************************************/
void AGenericDoor::ToggleLock(void)
{
	m_isLocked = !m_isLocked;
}

/******************************************************************************/
bool AGenericDoor::IsDoorLocked(void)
{
	return m_isLocked;
}
