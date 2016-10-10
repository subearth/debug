// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "OxygenTank.h"
#include "CharacterControl/SubEarthCharacter.h"

/******************************************************************************/
AOxygenTank::AOxygenTank()
{
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.9f, 0.2f));
	m_objectCollider->bHiddenInGame = false;
	m_pickupType = GENERIC_KEY;
}

/******************************************************************************/
void AOxygenTank::ExecuteAction1(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AOxygenTank::ExecuteAction1"));
}

/******************************************************************************/
void AOxygenTank::ExecuteAction2(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AOxygenTank::ExecuteAction2"));
}

/******************************************************************************/
void AOxygenTank::ExecuteAction3(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AOxygenTank::ExecuteAction3"));
}

/******************************************************************************/
void AOxygenTank::SetDefaultInHandOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(21.0f, 10.5f, 50.5f);
}

/******************************************************************************/
void AOxygenTank::SetDefaultWorldOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(-21.0f, -10.5f, -50.5f);
}
