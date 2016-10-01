// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Pocket.h"


/******************************************************************************/
APocket::APocket()
{
	m_objectCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	m_objectCollider->bHiddenInGame = false;

	m_pickupInPocket = NULL;
	m_isPocketEmpty = true;
}

/******************************************************************************/
void APocket::SetRelativePosition(FVector position)
{
	m_objectRoot->RelativeLocation = position;
}

/******************************************************************************/
bool APocket::IsPocketEmpty()
{
	return m_isPocketEmpty;
}

/******************************************************************************/
APickup* APocket::TakeItemOutOfPocket(void)
{
	APickup* pickup = m_pickupInPocket;
	m_pickupInPocket = NULL;
	m_isPocketEmpty = true;

	return pickup;
}

/******************************************************************************/
void APocket::PlaceItemInPocket(APickup* pickup)
{
	m_pickupInPocket = pickup;
	m_isPocketEmpty = false;
}
