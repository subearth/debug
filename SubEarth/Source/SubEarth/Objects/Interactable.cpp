// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Interactable.h"

#include "CharacterControl/SubEarthCharacter.h"

/******************************************************************************/
AInteractable::AInteractable()
{
	FString name = GetName();

	FString RootName = name + "Root";
	m_objectRoot = CreateDefaultSubobject<USceneComponent>(*RootName);
	RootComponent = m_objectRoot;

	FString MeshName = name + "Mesh";
	m_objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));
	m_objectMesh->SetupAttachment(m_objectRoot);

	FString ColliderName = name + "Collider";
	m_objectCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_objectCollider->SetupAttachment(m_objectRoot);

	// Enable the tick call back, but start with it disabled
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

/******************************************************************************/
USceneComponent* AInteractable::GetObjectRoot()
{
	return m_objectRoot;
}

/******************************************************************************/
AInteractable::Interactable_e  AInteractable::GetInteractableType(void)
{
	return m_interactableType;
}

/******************************************************************************/
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AInteractable BeginPlay started"));
}

/******************************************************************************/
void AInteractable::EnableAnimation(void)
{
	SetActorTickEnabled(true);
}

/******************************************************************************/
void AInteractable::DisableAnimation(void)
{
	SetActorTickEnabled(false);
}

/******************************************************************************/
void AInteractable::Tick(float DeltaTime)
{
	// This function is turned off by default. The derived class can turn it on if 
	// animation is needed.
	Super::Tick(DeltaTime);

	ExecuteAnimation(DeltaTime);
}

/******************************************************************************/
void AInteractable::UpdateLocAndRot(FVector delta_loc, FRotator delta_rot)
{
	UE_LOG(LogTemp, Log, TEXT("APickup::ExecutePrimaryAction  This function is meant to be overridden!"));
}
