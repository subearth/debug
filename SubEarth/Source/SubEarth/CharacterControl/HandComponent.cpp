// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "CharacterControl/HandComponent.h"
#include "Objects/JammedDoor.h"
#include "CharacterControl/SubEarthCharacter.h"
#include <string> 
#include "Objects/OxygenTank.h"
#include "HUD/SubEarthHUD.h"

/******************************************************************************/
UHandComponent::UHandComponent()
{
	m_interactableComponentType = HAND;
	m_isHandLatched = false;
	m_latchedInteractable = NULL;
	m_isHandEmpty = true;
	m_pickupInHand = NULL;
	m_overlappedInteractable = NULL;
	m_overlappedInterComp = NULL;

	m_objectMesh->bGenerateOverlapEvents = false;

	m_objectCollider->bGenerateOverlapEvents = true;
	m_objectCollider->OnComponentBeginOverlap.AddDynamic(this, &UHandComponent::BeginOverlap);
	m_objectCollider->OnComponentEndOverlap.AddDynamic(this, &UHandComponent::EndOverlap);
	m_objectCollider->SetWorldScale3D(FVector(0.35f, 0.20f, 0.075f));
	m_objectCollider->SetWorldLocation(FVector(0.f, 0.f, -4.f));
	m_objectCollider->bHiddenInGame = true;
	m_savedCollider = m_objectCollider;

	// Add the hand mesh to the left and right mesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HandMesh(TEXT("StaticMesh'/Game/Assets/Character/Hand'"));
	if (HandMesh.Object)
	{
		m_objectMesh->SetStaticMesh(HandMesh.Object);
		m_objectMesh->SetRelativeLocation(FVector(0.f, -2.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(-45.f, 180.f, 0.f));	
		//m_objectMesh->bHiddenInGame = true;
	}
}

/******************************************************************************/
void UHandComponent::ExecutePrimaryAction(APickup* pickup)
{
	UE_LOG(LogTemp, Log, TEXT("UHandComponent::ExecutePrimaryAction"));
}


/******************************************************************************/
void UHandComponent::ExecuteActionForTick(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (m_isHandLatched)
	{
		// Compute the delta location and rotation from last time
		// Note: These computations may have issues with Gimbal Lock. If this occurs, we will have
		// to update these to use quaternions
		USceneComponent* motion_ctrl = m_savedObjectRoot->GetAttachParent();
		FVector delta_loc = m_lastLatchedLocation - motion_ctrl->RelativeLocation;
		FRotator delta_rot = m_lastLatchedRotation - motion_ctrl->RelativeRotation;

		// Update the last location and rotation
		m_lastLatchedLocation = motion_ctrl->RelativeLocation;
		m_lastLatchedRotation = motion_ctrl->RelativeRotation;

		m_latchedInteractable->UpdateLocAndRot(delta_loc, delta_rot, GetName());
	}
}

/******************************************************************************/
void UHandComponent::PickupObject(APickup* pickup_obj)
{
	// Drop what's in our hand and pick up the other object
	if (!m_isHandEmpty)
	{
		DropObject();
	}

	pickup_obj->PrimaryActorTick.SetTickFunctionEnable(false);
	pickup_obj->AttachToComponent(m_savedObjectRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
	pickup_obj->SetDefaultInHandOrientation();

	pickup_obj->SetActorEnableCollision(false);

	m_pickupInHand = pickup_obj;
	m_overlappedInteractable = NULL; // We picked it up, therefore it is no longer overlapping
	m_isHandEmpty = false;

	UE_LOG(LogTemp, Log, TEXT("UHandComponent::PickupObject %s"), *(m_pickupInHand->GetName()));

	/*	if ((GetWorld()->GetMapName()) == "DemoMap" && (m_pickupInHand->GetName()) == "FlashLight_5")
	{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Switch the flashlight off to change game mode!"));
	UE_LOG(LogTemp, Log, TEXT("Switch the flashlight off to change game mode!"));
	// Message to denote that switching on/off the flashlight would change the map
	}
	*/
}

/******************************************************************************/
void UHandComponent::DropObject()
{
	UE_LOG(LogTemp, Log, TEXT("UHandComponent::DropObject %s"), *(m_pickupInHand->GetName()));

	m_pickupInHand->PrimaryActorTick.SetTickFunctionEnable(true);
	m_pickupInHand->SetActorEnableCollision(true);
	m_pickupInHand->SetDefaultWorldOrientation();
	m_pickupInHand->DetachRootComponentFromParent();

	// Only overwrite the overlapped object if the overlapped object is not already set.
	// Use case: if you let go of the door lever while it is in the door lever hole. 
	// By doing this we are saying, "the interactable object has higher priority than the
	// pickup object we just dropped".
	if (m_overlappedInteractable == NULL)
	{
		m_overlappedInteractable = (AInteractable*)m_pickupInHand; // We just dropped it, therefore it is currently overlapping
	}

	m_pickupInHand = NULL;
	m_isHandEmpty = true;
}

/******************************************************************************/
void UHandComponent::PressButton1(void)
{
	// Used for propolsion
}

/******************************************************************************/
void UHandComponent::PressButton2(void)
{
	// If the hand is not empty
	if (m_pickupInHand != NULL)
	{
		// If the hand is not overlapping an interactable
		if (m_overlappedInteractable == NULL)
		{
			m_pickupInHand->ExecuteAction1();
		}
		else
		{
			m_pickupInHand->ExecuteAction1(m_overlappedInteractable);
		}
	}
}

/******************************************************************************/
void UHandComponent::PressButton3(void)
{
	// If the hand is not empty
	if (m_pickupInHand != NULL)
	{
		// If the hand is not overlapping an interactable
		if (m_overlappedInteractable == NULL)
		{
			m_pickupInHand->ExecuteAction2();
		}
		else
		{
			m_pickupInHand->ExecuteAction2(m_overlappedInteractable);
		}
	}
}

/******************************************************************************/
void UHandComponent::PressButton4(void)
{
	// If the hand is not empty
	if (m_pickupInHand != NULL)
	{
		// If the hand is not overlapping an interactable
		if (m_overlappedInteractable == NULL)
		{
			m_pickupInHand->ExecuteAction3();
		}
		else
		{
			m_pickupInHand->ExecuteAction3(m_overlappedInteractable);
		}
	}
}

/******************************************************************************/
void UHandComponent::LatchHandToInteractable(AInteractable* interactable)
{
	// The goal here is that while latch, movement of the hand translates to some
	// kind of movement on the interactable. Eventually, we may want to actually
	// attach the mesh of the hand to the object (aka, disconnect it from the 
	// motion controllers motion and attached it to the interactable).

	m_isHandLatched = true;
	m_latchedInteractable = interactable;
	EnableTick();

	USceneComponent* motion_ctrl = m_savedObjectRoot->GetAttachParent();
	m_lastLatchedLocation = motion_ctrl->RelativeLocation;
	m_lastLatchedRotation = motion_ctrl->RelativeRotation;
}

/******************************************************************************/
void UHandComponent::ReleaseHand(void)
{
	m_isHandLatched = false;
	m_latchedInteractable = NULL;
	DisableTick();
}

/******************************************************************************/
void UHandComponent::BeginOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (otherActor->IsA(AInteractable::StaticClass())) // Type check before casting
	{
		UE_LOG(LogTemp, Log, TEXT("UHandComponent::BeginOverlap (1) with object: %s"), *(otherActor->GetName()));
		m_overlappedInteractable = (AInteractable*)otherActor;
	}
	else if (otherActor->IsA(ASubEarthCharacter::StaticClass())) // Type check before casting
	{
		ASubEarthCharacter* sub = (ASubEarthCharacter*)otherActor;
		UInteractableComponent* component = sub->GetOverlappedComponent(otherComponent);

		if (component != NULL)
		{
			UE_LOG(LogTemp, Log, TEXT("UHandComponent::BeginOverlap (2) with object: %s"), *(otherActor->GetName()));
			m_overlappedInterComp = component;
		}
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("UHandComponent::BeginOverlap object %s is not an interactable object"), *(otherActor->GetName()));
	}
}

/******************************************************************************/
void UHandComponent::EndOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex)
{
	if (otherActor->IsA(AInteractable::StaticClass())) // Type check before casting
	{
		UE_LOG(LogTemp, Log, TEXT("UHandComponent::EndOverlap (1) with object: %s"), *(otherActor->GetName()));
		m_overlappedInteractable = NULL;
	}
	else if (otherActor->IsA(ASubEarthCharacter::StaticClass())) // Type check before casting
	{
		ASubEarthCharacter* sub = (ASubEarthCharacter*)otherActor;
		UInteractableComponent* component = sub->GetOverlappedComponent(otherComponent);

		if (component != NULL)
		{
			UE_LOG(LogTemp, Log, TEXT("UHandComponent::EndOverlap (2) with object: %s"), *(otherActor->GetName()));
			m_overlappedInterComp = NULL;
		}
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("UHandComponent::EndOverlap object %s is not an interactable object"), *(otherActor->GetName()));
	}
}

/******************************************************************************/
void UHandComponent::UseHand()
{
	// If the hand is overlapping an interactable object in the world
	if (m_overlappedInteractable != NULL)
	{
		switch (m_overlappedInteractable->GetInteractableType())
		{
		case AInteractable::PICKUP_OBJECT:
		{
			APickup::Pickup_e pickup_type = ((APickup*)m_overlappedInteractable)->GetPickupType();

			if (pickup_type == APickup::DOOR_LEVER)
			{
				ADoorLever* lever = (ADoorLever*)m_overlappedInteractable;

				if (lever->IsAttachedToDoor())
				{
					LatchHandToInteractable(m_overlappedInteractable);
				}
				else
				{
					PickupObject((APickup*)m_overlappedInteractable);
				}
			}
			else
			{
				PickupObject((APickup*)m_overlappedInteractable);
			}

			break;
		}
		case AInteractable::GENERIC_DOOR:
		{
			if (m_isHandEmpty)
			{
				m_overlappedInteractable->ExecutePrimaryAction();
			}
			else
			{
				m_overlappedInteractable->ExecutePrimaryAction(m_pickupInHand);
			}
			break;
		}
		/*case AInteractable::TOOL_BOX:
		{
		m_overlappedInteractable->ExecutePrimaryAction();
		break;
		}*/
		case AInteractable::MOON_DOOR_CONTROL_PANEL:
		{
			m_overlappedInteractable->ExecutePrimaryAction();
			break;
		}
		case AInteractable::JAMMED_DOOR:
		{
			// Save a pointer to the overlapped door. If the pickup is dropped,
			// the hand starts calling begin/end overlaps with objects, which may
			// change our overlapped interactable
			AJammedDoor* door = (AJammedDoor*)m_overlappedInteractable;

			if (door->IsLeverInPlace())
			{
				UE_LOG(LogTemp, Log, TEXT("UHandComponent::UseHand  Must turn the lever"));
			}
			else
			{
				if (m_isHandEmpty)
				{
					m_overlappedInteractable->ExecutePrimaryAction();
				}
				else
				{
					APickup::Pickup_e pickup_type = m_pickupInHand->GetPickupType();

					if (pickup_type == APickup::DOOR_LEVER)
					{
						// Save a pointer to the pickup and overlapped door. Once an object is dropped,
						// the hand starts calling begin/end overlaps with objects. We need to keep a 
						// pointer to these. 
						APickup* lever = m_pickupInHand;

						// Drop the pickup so that we can attached it to the door.
						DropObject();

						door->ExecutePrimaryAction(lever);
					}
					else
					{
						UE_LOG(LogTemp, Log, TEXT("UHandComponent::UseHand  %s can't fit here"), *(m_pickupInHand->GetName()));
					}
				}
			}
			break;
		}
		default:
			// Do nothing
			break;
		}
	}
	// Else if the hand is overlapping an interactable component on the actor
	else if (m_overlappedInterComp != NULL)
	{
		switch (m_overlappedInterComp->GetInteractableComponentType())
		{
		case UInteractableComponent::POCKET:
		{
			UPocketComponent* pocket = (UPocketComponent*)m_overlappedInterComp;

			if (pocket->IsPocketEmpty() && !m_isHandEmpty)
			{
				pocket->PlaceItemInPocket(m_pickupInHand);
				m_isHandEmpty = true;
				m_pickupInHand = NULL;
			}
			else if (!pocket->IsPocketEmpty() && m_isHandEmpty)
			{
				APickup* pickup = pocket->TakeItemOutOfPocket();
				PickupObject(pickup);
			}
			else if (!pocket->IsPocketEmpty() && !m_isHandEmpty)
			{
				APickup* pickup = pocket->TakeItemOutOfPocket();
				pocket->PlaceItemInPocket(m_pickupInHand);
				PickupObject(pickup);
			}
			break;
		}
		case UInteractableComponent::OXYGEN_TANK_SLOT:
		{
			UOxygenTankSlot* ots = (UOxygenTankSlot*)m_overlappedInterComp;

			// Ensure we are holding an oxygen tank.
			// Tank Slot is empty and we have something in our hand
			if (ots->IsEmpty() && !m_isHandEmpty)
			{
				if (m_pickupInHand->GetPickupType() == APickup::OXYGEN_TANK)
				{
					// Place the Tank in the Tank Slot
					ots->PlaceTankInSlot(m_pickupInHand);
					m_isHandEmpty = true;
					m_pickupInHand = NULL;
				}
			}
			// Tank Slot has a Tank and our hand is empty:
			else if (!ots->IsEmpty() && m_isHandEmpty)
			{
				// Take the Tank from the Tank Slot:
				APickup* pickup = ots->TakeTankFromSlot();
				PickupObject(pickup);
			}
			// Tank Slot has a Tank and our Hand has a Tank: 
			else if (!ots->IsEmpty() && !m_isHandEmpty)
			{
				if (m_pickupInHand->GetPickupType() == APickup::OXYGEN_TANK)
				{
					// Drop tank and replace with Tank in Hand:
					ots->DropTankInSlot();
					ots->PlaceTankInSlot(m_pickupInHand);
					m_isHandEmpty = true;
					m_pickupInHand = NULL;
				}
			}

			break;
		}
		}
	}
	// If we were holding something, drop it.
	else if (!m_isHandEmpty)
	{
		DropObject();
	}
}

/******************************************************************************/
void UHandComponent::TranslateUp(void)
{
	FVector curr_loc = m_savedObjectRoot->RelativeLocation;
	curr_loc.Z++;
	m_savedObjectRoot->RelativeLocation = curr_loc;
}

/******************************************************************************/
void UHandComponent::TranslateDown(void)
{
	FVector curr_loc = m_savedObjectRoot->RelativeLocation;
	curr_loc.Z--;
	m_savedObjectRoot->RelativeLocation = curr_loc;
}

/******************************************************************************/
void UHandComponent::SetRelative3DScaleOnMesh(FVector scale)
{
	m_objectMesh->SetRelativeScale3D(scale);
}
