// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/DoorLever.h"
#include "Objects/JammedDoor.h"
#include "CharacterControl/SubEarthCharacter.h"
#include "CharacterControl/HandComponent.h"

/******************************************************************************/
ADoorLever::ADoorLever()
{
	m_objectCollider->SetWorldScale3D(FVector(0.15f, 0.4f, 0.15f));
	m_objectCollider->bHiddenInGame = true;
	m_pickupType = DOOR_LEVER;
	m_leverInDoor = false;
	m_doorAttachedTo = NULL;
	m_leftColliderGrabbed = false;
	m_rightColliderGrabbed = false;
	m_leftHand = NULL;
	m_rightHand = NULL;

	FString name = GetName();

	FString ColliderName = name + "LeftCollider";
	m_leftCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_leftCollider->SetupAttachment(m_objectRoot);
	m_leftCollider->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
	m_leftCollider->SetRelativeLocation(FVector(16.5f, -18.0f, 0.0f)); //40
	m_leftCollider->bHiddenInGame = true;
	m_leftCollider->OnComponentBeginOverlap.AddDynamic(this, &ADoorLever::LeftColliderBeginOverlap);
	m_leftCollider->OnComponentEndOverlap.AddDynamic(this, &ADoorLever::LeftColliderEndOverlap);

	ColliderName = name + "RightCollider";
	m_rightCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_rightCollider->SetupAttachment(m_objectRoot);
	m_rightCollider->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
	m_rightCollider->SetRelativeLocation(FVector(0.0f, 22.0f, 0.0f)); //48
	m_rightCollider->bHiddenInGame = true;
	m_rightCollider->OnComponentBeginOverlap.AddDynamic(this, &ADoorLever::RightColliderBeginOverlap);
	m_rightCollider->OnComponentEndOverlap.AddDynamic(this, &ADoorLever::RightColliderEndOverlap);

	m_approxRadius = 34.0f; // average halfway between center of two levers an left/right collider

	static ConstructorHelpers::FObjectFinder<UStaticMesh> door_lever_mesh(TEXT("StaticMesh'/Game/Assets/Objects/Tool/Tool.Tool'"));
	if (door_lever_mesh.Object)
	{
		m_objectMesh->SetStaticMesh(door_lever_mesh.Object);
		m_objectMesh->SetupAttachment(m_objectRoot);
		m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	}
}

/******************************************************************************/
void ADoorLever::ExecuteAction1(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("ADoorLever::ExecuteAction1"));
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
}

/******************************************************************************/
void ADoorLever::SetDefaultWorldOrientation(void)
{
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
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
void ADoorLever::UpdateLocAndRot(FVector delta_loc, FRotator delta_rot, FString name)
{
	// Map the up and down translation of the hand motion to rotation of the lever

	// If only one hand is overlapped and you try to pull the trigger
	if ((m_rightHand != NULL && m_leftHand == NULL) || (m_rightHand == NULL && m_leftHand != NULL))
	{
		UE_LOG(LogTemp, Log, TEXT("ADoorLever::UpdateLocAndRot The door is too tight. Must use both hands"));
	}
	
	// Both hands must overlap
	if (m_rightHand != NULL && m_leftHand != NULL)
	{
		// When each hand pulls the trigger, this function will be called.
		// Once both hands are overlapping the colliders and the trigger is pulled
		// Then allow rotation of the lever
		if (name == m_rightHand->GetName())
		{
			m_rightColliderGrabbed = true;
		}

		if (name == m_leftHand->GetName())
		{
			m_leftColliderGrabbed = true;
		}

		// You must be grabbing with both hands
		if (m_rightColliderGrabbed && m_leftColliderGrabbed)
		{
			// The motion only comes from one hand.  This is an easier solution than mapping both hands and summing the result into a rotation
			if (name == m_rightHand->GetName())
			{
				FQuat quat = FQuat(FRotator(0.f, (asinf((delta_loc.Z + delta_loc.X) / m_approxRadius) * 57.2958), 0.0f));

				FTransform trans = GetTransform();
				trans.ConcatenateRotation(quat);
				SetActorTransform(trans);

				FRotator curr_rot = GetActorRotation();
				UE_LOG(LogTemp, Log, TEXT("ADoorLever::UpdateLocAndRot  Z=%3.2f   roll=%3.2f pitch=%3.2f yaw=%3.2f"), delta_loc.Z, curr_rot.Roll, curr_rot.Pitch, curr_rot.Yaw);

				// When rotated 90 deg CCW from initial position
				if (curr_rot.Pitch <= 25.0f && m_doorAttachedTo->IsDoorClosed())
				{
					if (m_leverInDoor && m_doorAttachedTo != NULL)
					{
						m_doorAttachedTo->ToggleDoorOpenClosed();
					}
				}
			}
		}
	}
}

/******************************************************************************/
void ADoorLever::LeftColliderBeginOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (otherActor->IsA(ASubEarthCharacter::StaticClass())) // Type check before casting
	{
		ASubEarthCharacter* sub = (ASubEarthCharacter*)otherActor;
		UInteractableComponent* component = sub->GetOverlappedComponent(otherComponent);

		if (component != NULL)
		{
			m_leftHand = component;
		}
	}
}

/******************************************************************************/
void ADoorLever::LeftColliderEndOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex)
{
	m_leftColliderGrabbed = false;
	m_leftHand = NULL;
}


/******************************************************************************/
void ADoorLever::RightColliderBeginOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (otherActor->IsA(ASubEarthCharacter::StaticClass())) // Type check before casting
	{
		ASubEarthCharacter* sub = (ASubEarthCharacter*)otherActor;
		UInteractableComponent* component = sub->GetOverlappedComponent(otherComponent);

		if (component != NULL)
		{
			m_rightHand = component;
		}
	}
}

/******************************************************************************/
void ADoorLever::RightColliderEndOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex)
{
	m_rightColliderGrabbed = false;
	m_rightHand = NULL;
}
