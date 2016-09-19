// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "ColorChangingOrb.h"


/******************************************************************************/
AColorChangingOrb::AColorChangingOrb()
{
	objectCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f)); // Needs to be pushed down one more level
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
