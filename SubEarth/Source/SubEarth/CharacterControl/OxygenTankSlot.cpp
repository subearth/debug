// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "OxygenTankSlot.h"
#include "Objects/OxygenTank.h"


/******************************************************************************/
UOxygenTankSlot::UOxygenTankSlot()
{
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.6f));
	m_objectCollider->bHiddenInGame = false;

	m_interactableComponentType = OXYGEN_TANK_SLOT;
	m_tankInSlot = NULL;
}

/******************************************************************************/
void UOxygenTankSlot::ExecutePrimaryAction(APickup* pickup)
{
	UE_LOG(LogTemp, Log, TEXT("UOxygenTankSlot::ExecutePrimaryAction"));
}

bool UOxygenTankSlot::IsEmpty(void)
{
	if (m_tankInSlot == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

APickup* UOxygenTankSlot::TakeTankFromSlot(void)
{
	APickup* pickup = NULL;

	if (m_tankInSlot != NULL)
	{
		pickup = m_tankInSlot;
		pickup->DetachRootComponentFromParent();
		pickup->SetDefaultInHandOrientation();
		pickup->SetActorEnableCollision(true);

		m_tankInSlot = NULL;

		UE_LOG(LogTemp, Log, TEXT("Took %s out of pocket"), *pickup->GetName());
	}

	return pickup;
}

void UOxygenTankSlot::PlaceTankInSlot(APickup* pickup)
{
	if (m_tankInSlot == NULL)
	{
		m_tankInSlot = pickup;

		pickup->AttachToComponent(m_objectRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		pickup->SetDefaultWorldOrientation(); // TODO this create orientation for "In Pocket"
		pickup->SetActorEnableCollision(false);

		UE_LOG(LogTemp, Log, TEXT("Placed %s in pocket"), *pickup->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add %s to the pocket when the pocket is not empty!"), *pickup->GetName());
	}
}

void UOxygenTankSlot::DropTankInSlot(void)
{
	m_tankInSlot->SetActorEnableCollision(true);
	m_tankInSlot->DetachRootComponentFromParent();
	m_tankInSlot = NULL;
}

float UOxygenTankSlot::GetTankInitialLevel(void)
{
	if (m_tankInSlot == NULL)
	{
		return 0.f;
	}
	else
	{
		AOxygenTank* myTank = (AOxygenTank*)m_tankInSlot;
		return myTank->GetInitialOxygen();
	}
}
float UOxygenTankSlot::GetTankCurrentLevel(void)
{
	if (m_tankInSlot == NULL)
	{
		return 0.f;
	}
	else
	{
		AOxygenTank* myTank = (AOxygenTank*)m_tankInSlot;
		return myTank->GetCurrentOxygen();
	}
}
void UOxygenTankSlot::SetTankCurrentLevel(float value)
{
	if (m_tankInSlot != NULL)
	{
		AOxygenTank* myTank = (AOxygenTank*)m_tankInSlot;
		myTank->SetCurrentOxygen(value);
	}
}