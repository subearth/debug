// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/DoorLever.h"
#include "Objects/JammedDoor.h"

/******************************************************************************/
ADoorLever::ADoorLever()
{
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.9f, 0.2f));
	m_objectCollider->bHiddenInGame = false;
	m_pickupType = DOOR_LEVER;
	m_leverInDoor = false;
	m_doorAttachedTo = NULL;

	FString name = GetName();

	FString ColliderName = name + "LeftCollider";
	m_leftCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_leftCollider->SetupAttachment(m_objectRoot);
	m_leftCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_leftCollider->SetRelativeLocation(FVector(33.0f, -40.0f, 0.0f));
	m_leftCollider->bHiddenInGame = true;

	ColliderName = name + "RightCollider";
	m_rightCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_rightCollider->SetupAttachment(m_objectRoot);
	m_rightCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_rightCollider->SetRelativeLocation(FVector(0.0f, 48.0f, 0.0f));
	m_rightCollider->bHiddenInGame = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> door_lever_mesh(TEXT("StaticMesh'/Game/Assets/Objects/Tool/Tool.Tool'"));
	if (door_lever_mesh.Object)
	{
		m_objectMesh->SetStaticMesh(door_lever_mesh.Object);
		m_objectMesh->SetupAttachment(m_objectRoot);
		m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
}

/******************************************************************************/
void ADoorLever::ExecuteAction1(AInteractable* interactable)
{
	if (interactable != NULL)
	{
		Interactable_e interactable_type = interactable->GetInteractableType();
	}
}

/******************************************************************************/
void ADoorLever::ExecuteAction2(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("ADoorLever::ExecuteAction2"));
}

/******************************************************************************/
void ADoorLever::ExecuteAction3(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("ADoorLever::ExecuteAction3"));
}

/******************************************************************************/
void ADoorLever::SetDefaultInHandOrientation(void)
{
	SetActorRotation(FRotator(21.0f, 10.5f, 50.5f));
	UE_LOG(LogTemp, Log, TEXT(" ADoorLever::SetDefaultInHandOrientation"));
}

/******************************************************************************/
void ADoorLever::SetDefaultWorldOrientation(void)
{
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	UE_LOG(LogTemp, Log, TEXT(" ADoorLever::SetDefaultWorldOrientation"));
}

/******************************************************************************/
void ADoorLever::SetupAttachToDoorParams(AJammedDoor* door)
{
	// hide the main collider
	m_objectCollider->SetHiddenInGame(true);
	m_leftCollider->SetHiddenInGame(false);
	m_rightCollider->SetHiddenInGame(false);
	m_leverInDoor = true;
	m_doorAttachedTo = door;
	// Unfortunately this disables collisions all together, not just on the one
	//m_objectCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//m_leftCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//m_rightCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

/******************************************************************************/
bool ADoorLever::IsAttachedToDoor(void)
{
	return m_leverInDoor;
}

/******************************************************************************/
void ADoorLever::UpdateLocAndRot(FVector delta_loc, FRotator delta_rot)
{
	// Map the up and down translation of the hand motion to rotation of the lever
	FRotator curr_rot = GetActorRotation();
	//FRotator curr_rot = m_objectRoot->RelativeRotation;
	UE_LOG(LogTemp, Log, TEXT("ADoorLever::UpdateLocAndRot BEFORE:  Z=%3.2f    roll=%3.2f pitch=%3.2f yaw=%3.2f"), delta_loc.Z, curr_rot.Roll, curr_rot.Pitch, curr_rot.Yaw);
	curr_rot.Roll  -= delta_loc.Z * 2.0f;
	//curr_rot.Pitch = 90.0f;
	//curr_rot.Yaw   = -90.0f;
	//FRotator curr_rot = FRotator(delta_loc.Z, 0.0f, 0.0f);
	UE_LOG(LogTemp, Log, TEXT("ADoorLever::UpdateLocAndRot  AFTER:  Z=%3.2f    roll=%3.2f pitch=%3.2f yaw=%3.2f"), delta_loc.Z, curr_rot.Roll, curr_rot.Pitch, curr_rot.Yaw);
	SetActorRelativeRotation(curr_rot);

	if (true)
	{
		if (m_leverInDoor && m_doorAttachedTo != NULL)
		{
			UE_LOG(LogTemp, Log, TEXT("ADoorLever::ExecutePrimaryAction Toggle door!"));
			m_doorAttachedTo->ToggleDoorOpenClosed();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ADoorLever::ExecutePrimaryAction  Override me!"));
		}
	}
}
