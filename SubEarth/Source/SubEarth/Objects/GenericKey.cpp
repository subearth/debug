// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/GenericKey.h"
#include "Objects/GenericDoor.h"


/******************************************************************************/
AGenericKey::AGenericKey()
{
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.9f, 0.2f));
	m_objectCollider->bHiddenInGame = false;
	m_pickupType = GENERIC_KEY;
}

/******************************************************************************/
void AGenericKey::ExecuteAction1(AInteractable* interactable)
{
	Interactable_e interactable_type = interactable->GetInteractableType();

	if (interactable_type == GENERIC_DOOR)
	{
		AGenericDoor* door = (AGenericDoor*)interactable;
		door->ToggleLock();

		if (door->IsDoorLocked())
		{
			UE_LOG(LogTemp, Log, TEXT("AGenericKey::ExecuteAction1  DOOR IS LOCKED"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("AGenericKey::ExecuteAction1  DOOR IS UNLOCKED"));
		}
	}
}

/******************************************************************************/
void AGenericKey::ExecuteAction2(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AGenericKey::ExecuteAction2"));
}

/******************************************************************************/
void AGenericKey::ExecuteAction3(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AGenericKey::ExecuteAction3"));
}

/******************************************************************************/
void AGenericKey::SetDefaultInHandOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(21.0f, 10.5f, 50.5f);
}

/******************************************************************************/
void AGenericKey::SetDefaultWorldOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(-21.0f, -10.5f, -50.5f);
}

