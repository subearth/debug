// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "GenericDoor.h"

/******************************************************************************/
AGenericDoor::AGenericDoor()
{
	m_interactableType = GENERIC_DOOR;

	// Setup the doorknob interactable size
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_objectCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 1.1f));
	m_objectCollider->bHiddenInGame = false;
	m_isLocked = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> my_mesh(TEXT("StaticMesh'/Game/Assets/Objects/GenericDoor/Shape_Cube.Shape_Cube'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> my_material(TEXT("Material'/Game/Assets/Objects/GenericDoor/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished'"));

	if (my_mesh.Object)
	{
		m_objectMesh->SetStaticMesh(my_mesh.Object);
		//m_objectMesh->SetMaterial(0, my_material.Object);
		m_objectMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(0.05f, 1.1f, 2.2f));
	}
}

/******************************************************************************/
void AGenericDoor::ExecutePrimaryAction(APickup* pickup)
{
	if (m_isLocked)
	{
		// TODO print this out on HUD???
		UE_LOG(LogTemp, Log, TEXT("AGenericDoor::ExecutePrimaryAction  CANNOT OPEN, DOOR IS LOCKED"));
	}
	else
	{
		// TODO Animate opening the door here.
		UE_LOG(LogTemp, Log, TEXT("AGenericDoor::ExecutePrimaryAction  OPENING DOOR"));
	}
	
}

/******************************************************************************/
void AGenericDoor::ToggleLock(void)
{
	m_isLocked = !m_isLocked;
}

/******************************************************************************/
bool AGenericDoor::IsDoorLocked(void)
{
	return m_isLocked;
}
