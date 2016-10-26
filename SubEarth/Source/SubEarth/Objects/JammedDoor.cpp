// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/JammedDoor.h"

/******************************************************************************/
AJammedDoor::AJammedDoor()
{
	m_interactableType = JAMMED_DOOR;
	m_animState = NOT_ANIMATING;
	m_isClosed = true;
	m_lever = NULL;

	// Setup the doorknob interactable size
	m_objectCollider->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	m_objectCollider->SetRelativeLocation(FVector(-190.f, -25.f, 160.f));
	m_objectCollider->bHiddenInGame = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> my_mesh1(TEXT("StaticMesh'/Game/Assets/Buildings/DoorCenter/DoorCenterMesh'"));

	if (my_mesh1.Object)
	{
		m_objectMesh->SetStaticMesh(my_mesh1.Object);
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

			lever->PrimaryActorTick.SetTickFunctionEnable(false);
			lever->AttachToComponent(m_objectRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
			lever->SetActorRelativeLocation(FVector(-190.f, -25.f, 160.f));
			lever->SetActorRotation(FRotator(90.0f, 90.0f, 0.f));

			lever->SetupAttachToDoorParams(this);

			m_lever = lever;

			// Disable the collision with the jammed door. It is not needed once the lever is placed
			m_objectCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("AJammedDoor::ExecutePrimaryAction Not a door lever"));
		}
	}
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

/******************************************************************************/
bool AJammedDoor::IsDoorClosed(void)
{
	return m_isClosed;
}

/******************************************************************************/
void AJammedDoor::ToggleDoorOpenClosed(void)
{
	if (m_isClosed)
	{
		UE_LOG(LogTemp, Log, TEXT("AJammedDoor::ToggleDoorOpenClosed OPENING"));
		m_animState = OPENING;
		m_isClosed = false;
		EnableAnimation();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AJammedDoor::ToggleDoorOpenClosed CLOSING"));
		m_animState = CLOSING;
		m_isClosed = true;
		EnableAnimation();
	}
}

/******************************************************************************/
void AJammedDoor::ExecuteAnimation(float delta_time)
{
	const float OPEN_RATE = 50.0f;
	const float CLOSE_RATE = 50.0f;
	const float Z_OPEN_POSITION = -300.0;
	const float Z_CLOSE_POSITION = 0.0f;

	static float z = Z_CLOSE_POSITION;

	switch (m_animState)
	{
		case NOT_ANIMATING:
		{
			// Do nothing
			break;
		}
		case OPENING:
		{
			z -= (OPEN_RATE * delta_time);

			if (z <= Z_OPEN_POSITION)
			{
				z = Z_OPEN_POSITION;
				m_animState = NOT_ANIMATING;
				DisableAnimation();
			}
			break;
		}
		case CLOSING:
		{
			z += (CLOSE_RATE * delta_time);

			if (z >= Z_CLOSE_POSITION)
			{
				z = Z_CLOSE_POSITION;
				m_animState = NOT_ANIMATING;
				DisableAnimation();
			}
			break;
		}
	}

	m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, z));
}
