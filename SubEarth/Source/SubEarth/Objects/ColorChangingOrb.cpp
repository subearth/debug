// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/ColorChangingOrb.h"


/******************************************************************************/
AColorChangingOrb::AColorChangingOrb()
{
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
}

/******************************************************************************/
void AColorChangingOrb::ExecuteAction1(void)
{
	UE_LOG(LogTemp, Log, TEXT("AColorChangingOrb::ExecuteAction1"));
}

/******************************************************************************/
void AColorChangingOrb::ExecuteAction2(void)
{
	UE_LOG(LogTemp, Log, TEXT("AColorChangingOrb::ExecuteAction2"));
}

/******************************************************************************/
void AColorChangingOrb::ExecuteAction3(void)
{
	UE_LOG(LogTemp, Log, TEXT("AColorChangingOrb::ExecuteAction3"));
}

/******************************************************************************/
void AColorChangingOrb::SetDefaultInHandOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(21.0f, 10.5f, 50.5f);
}

/******************************************************************************/
void AColorChangingOrb::SetDefaultWorldOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(-21.0f, -10.5f, -50.5f);
}
