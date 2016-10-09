// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Pickup.h"

/******************************************************************************/
APickup::APickup()
{
	m_interactableType = PICKUP_OBJECT;
}

APickup::Pickup_e  APickup::GetPickupType(void)
{
	return m_pickupType;
}

/******************************************************************************/
void APickup::ExecutePrimaryAction(APickup* pickup)
{
	// The action upon trigger pull is for the hand to pick up this object. 
	// There is no action on the object directly.
}

/******************************************************************************/
void APickup::SetDefaultInHandOrientation(void)
{
	// This is the default orientation of a Pickup. The derived class should overwrite this.
	m_objectRoot->RelativeRotation = FRotator(0.0f, 0.0f, 0.0f);
}

/******************************************************************************/
void APickup::SetDefaultWorldOrientation(void)
{
	// This is the default orientation of a Pickup. The derived class should overwrite this.
	m_objectRoot->RelativeRotation = FRotator(0.0f, 0.0f, 0.0f);
}
