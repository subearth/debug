// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Pickup.h"

/******************************************************************************/
APickup::APickup()
{

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

/* Keep these. We will end up needed OnPlayerHandOverlap or similar function
void APickup::PickupItem()
{
MyPlayerController->ShowInventory.Add(*pickupName);
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Added to inventory. Press I to see the list"));
Destroy();
}
*/
