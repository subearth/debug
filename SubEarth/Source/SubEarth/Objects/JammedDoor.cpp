// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/JammedDoor.h"
//#include "Objects/Pickup.h"
//#include "Objects/DoorLever.h"

/******************************************************************************/
AJammedDoor::AJammedDoor()
{
	m_interactableType = JAMMED_DOOR;
	m_lever = NULL;

	// Setup the doorknob interactable size
	m_objectCollider->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	m_objectCollider->SetRelativeLocation(FVector(-190.f, -25.f, 160.f));
	m_objectCollider->bHiddenInGame = false;
	m_isLocked = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> my_mesh1(TEXT("StaticMesh'/Game/Assets/Buildings/DoorCenter/DoorCenterMesh'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> my_material(TEXT("Material'/Game/Assets/Objects/GenericDoor/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished'"));

	if (my_mesh1.Object)
	{
		m_objectMesh->SetStaticMesh(my_mesh1.Object);
		//m_objectMesh->SetMaterial(0, my_material.Object);
		m_objectMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	}
}

/******************************************************************************/
void AJammedDoor::ExecutePrimaryAction(APickup* pickup)
{
	if (pickup == NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("AJammedDoor::ExecutePrimaryAction  The door is JAMMED. Cannot open"));
	}
	else
	{
		
		APickup::Pickup_e pickup_type = pickup->GetPickupType();

		if (pickup_type == APickup::DOOR_LEVER)
		{
			ADoorLever* lever = (ADoorLever*)pickup;

			//lever->SetActorEnableCollision(false);
			lever->PrimaryActorTick.SetTickFunctionEnable(false);
			lever->AttachToComponent(m_objectRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
			lever->SetActorRelativeLocation(FVector(-190.f, -25.f, 160.f));
			lever->SetActorRelativeRotation(FRotator(90.0f, 90.0f, 0.f));

			lever->SetupAttachToDoorParams();

			m_lever = lever;

			UE_LOG(LogTemp, Log, TEXT("AJammedDoor::ExecutePrimaryAction Lever attached to door"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("AJammedDoor::ExecutePrimaryAction Not a door lever"));
		}
		
	}
}

/******************************************************************************/
void AJammedDoor::ToggleLock(void)
{
	m_isLocked = !m_isLocked;
}

/******************************************************************************/
bool AJammedDoor::IsLeverInPlace(void)
{
	bool lever_in_place = true;
	if (m_lever == NULL)
	{
		lever_in_place = false;
	}
	return lever_in_place;
}



