// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Heart.h"



AHeart::AHeart()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeartMesh(TEXT("StaticMesh'/Game/Assets/Objects/ColorChangingOrbMesh'"));
	if (HeartMesh.Object)
	{
		m_objectMesh->SetStaticMesh(HeartMesh.Object);
		m_objectMesh->SetupAttachment(m_objectRoot);
		m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(0.04f, 0.04f, 0.04f));

		m_objectCollider->SetupAttachment(m_objectRoot);
		m_objectCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectCollider->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
		m_objectCollider->bHiddenInGame = true;
	}
}

/******************************************************************************/
void AHeart::ExecuteAction1(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AHeart::ExecuteAction1"));
}

/******************************************************************************/
void AHeart::ExecuteAction2(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AHeart::ExecuteAction2"));
}

/******************************************************************************/
void AHeart::ExecuteAction3(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AHeart::ExecuteAction3"));
}

/******************************************************************************/
void AHeart::SetDefaultInHandOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//m_objectRoot->RelativeRotation = FRotator(21.0f, 10.5f, 50.5f);
}

/******************************************************************************/
void AHeart::SetDefaultWorldOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//m_objectRoot->RelativeRotation = FRotator(-21.0f, -10.5f, -50.5f);
}