// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "OxygenTank.h"
#include "CharacterControl/SubEarthCharacter.h"

/******************************************************************************/
AOxygenTank::AOxygenTank()
{
	m_pickupType = OXYGEN_TANK;
	m_initialOxygen = 100.f;
	m_currentOxygen = m_initialOxygen;


	m_objectCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	m_objectCollider->SetWorldScale3D(FVector(0.3f, 0.3f, 1.0f));
	m_objectCollider->bHiddenInGame = false;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TankMesh(TEXT("StaticMesh'/Game/Assets/Objects/Tank/OxygenTankBlockout'"));
	if (TankMesh.Object)
	{
		m_objectMesh->SetStaticMesh(TankMesh.Object);
		
		m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
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
	m_objectRoot->RelativeRotation = FRotator(0.f, 90.f, 90.f);
	//m_objectRoot->RelativeRotation = FRotator(21.0f, 10.5f, 50.5f);
}

/******************************************************************************/
void AOxygenTank::SetDefaultWorldOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//m_objectRoot->RelativeRotation = FRotator(-21.0f, -10.5f, -50.5f);
}

/******************************************************************************/
float AOxygenTank::GetInitialOxygen(void)
{
	return m_initialOxygen;
}

/******************************************************************************/
float AOxygenTank::GetCurrentOxygen(void)
{
	return m_currentOxygen;
}

/******************************************************************************/
void AOxygenTank::SetCurrentOxygen(float value)
{
	m_currentOxygen = value;
}
