// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "CharacterControl/Hand.h"
#include "Objects/JammedDoor.h"
#include "CharacterControl/SubEarthCharacter.h"
#include <string> 
#include "Objects/OxygenTank.h"
#include "HUD/SubEarthHUD.h"


// Sets default values for this component's properties
UHand::UHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;

	// NOTE. The hands should really inherit from an InteractableComponent, then the tick
	// functions added here could be elevate and potentially used for all InteractableComponents.
	// Can be implemented in the same way Interactable implements this behavior.
	// Enable the tick call back, but start with it disabled
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	m_isHandLatched = false;
	m_latchedInteractable = NULL;

	FString HandName = GetName();

	FString RootName = HandName + "Root";
	handSceneComponent = CreateDefaultSubobject<USceneComponent>(FName(*RootName));
	m_savedHandSceneComponent = handSceneComponent;

	FString MeshName = HandName + "Mesh";
	handMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));	
	handMesh->SetupAttachment(handSceneComponent);
	handMesh->bGenerateOverlapEvents = false;

	FString ColliderName = HandName + "Collider";
	handCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	handCollider->bGenerateOverlapEvents = true;
	handCollider->OnComponentBeginOverlap.AddDynamic(this, &UHand::BeginOverlap);
	handCollider->OnComponentEndOverlap.AddDynamic(this, &UHand::EndOverlap);
	handCollider->SetWorldScale3D(FVector(0.3f, 0.3f, 0.05f));
	handCollider->SetWorldLocation(FVector(0.f, 0.f, -4.f));
	//handCollider->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
	handCollider->SetupAttachment(handSceneComponent);
	m_savedCollider = handCollider;
	
	// Start off holding nothing.
	m_isHandEmpty = true;
	m_pickupInHand = NULL;
	m_overlappedInteractable = NULL;
	m_overlappedInterComp = NULL;

}

// Called when the game starts
void UHand::BeginPlay()
{
	Super::BeginPlay();
}

/******************************************************************************/
void UHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_isHandLatched)
	{
		// Compute the delta location and rotation from last time
		// Note: These computations may have issues with Gimbal Lock. If this occurs, we will have
		// to update these to use quaternions
		USceneComponent* motion_ctrl = m_savedHandSceneComponent->GetAttachParent();
		FVector delta_loc = m_lastLatchedLocation - motion_ctrl->RelativeLocation;
		FRotator delta_rot = m_lastLatchedRotation - motion_ctrl->RelativeRotation;

		// Update the last location and rotation
		m_lastLatchedLocation = motion_ctrl->RelativeLocation;
		m_lastLatchedRotation = motion_ctrl->RelativeRotation;

		m_latchedInteractable->UpdateLocAndRot(delta_loc, delta_rot, GetName());
	}
}

/******************************************************************************/
void UHand::PickupObject(APickup* pickup_obj)
{
	// Drop what's in our hand and pick up the other object
	if (!m_isHandEmpty)
	{
		DropObject();
	}
	
	pickup_obj->PrimaryActorTick.SetTickFunctionEnable(false);
	pickup_obj->AttachToComponent(m_savedHandSceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	pickup_obj->SetDefaultInHandOrientation();
	
	pickup_obj->SetActorEnableCollision(false);
	
	m_pickupInHand = pickup_obj;
	m_overlappedInteractable = NULL; // We picked it up, therefore it is no longer overlapping
	m_isHandEmpty = false;

	UE_LOG(LogTemp, Log, TEXT("AHand::PickupObject %s"), *(m_pickupInHand->GetName()));
	
/*	if ((GetWorld()->GetMapName()) == "DemoMap" && (m_pickupInHand->GetName()) == "FlashLight_5")
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Switch the flashlight off to change game mode!"));
		UE_LOG(LogTemp, Log, TEXT("Switch the flashlight off to change game mode!"));
		// Message to denote that switching on/off the flashlight would change the map
	}
*/
}

/******************************************************************************/
void UHand::DropObject()
{
	UE_LOG(LogTemp, Log, TEXT("AHand::DropObject %s"), *(m_pickupInHand->GetName()));
	
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
void UHand::PressButton1(void)
{
	// Used for propolsion
}

/******************************************************************************/
void UHand::PressButton2(void)
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
void UHand::PressButton3(void)
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
void UHand::PressButton4(void)
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
void UHand::LatchHandToInteractable(AInteractable* interactable)
{
	// The goal here is that while latch, movement of the hand translates to some
	// kind of movement on the interactable. Eventually, we may want to actually
	// attach the mesh of the hand to the object (aka, disconnect it from the 
	// motion controllers motion and attached it to the interactable).

	m_isHandLatched = true;
	m_latchedInteractable = interactable;
	SetComponentTickEnabled(true);

	USceneComponent* motion_ctrl = m_savedHandSceneComponent->GetAttachParent();
	m_lastLatchedLocation = motion_ctrl->RelativeLocation;
	m_lastLatchedRotation = motion_ctrl->RelativeRotation;
}

/******************************************************************************/
void UHand::ReleaseHand(void)
{
	m_isHandLatched = false;
	m_latchedInteractable = NULL;
	SetComponentTickEnabled(false);
}

/******************************************************************************/
void UHand::BeginOverlap(UPrimitiveComponent* overlappedComponent,
	                     AActor* otherActor,
	                     UPrimitiveComponent* otherComponent,
	                     int32 otherBodyIndex,
	                     bool bFromSweep,
	                     const FHitResult& SweepResult)
{
	if (otherActor->IsA(AInteractable::StaticClass())) // Type check before casting
	{
		UE_LOG(LogTemp, Log, TEXT("UHand::BeginOverlap (1) with object: %s"), *(otherActor->GetName()));
		m_overlappedInteractable = (AInteractable*)otherActor;
	}
	else if (otherActor->IsA(ASubEarthCharacter::StaticClass())) // Type check before casting
	{
		ASubEarthCharacter* sub = (ASubEarthCharacter*)otherActor;
		UInteractableComponent* component = sub->GetOverlappedComponent(otherComponent);

		if (component != NULL)
		{
			UE_LOG(LogTemp, Log, TEXT("UHand::BeginOverlap (2) with object: %s"), *(otherActor->GetName()));
			m_overlappedInterComp = component;
		}
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("UHand::BeginOverlap object %s is not an interactable object"), *(otherActor->GetName()));
	}
}

/******************************************************************************/
void UHand::EndOverlap(UPrimitiveComponent* overlappedComponent,
	                   AActor* otherActor,
	                   UPrimitiveComponent* otherComponent,
	                   int32 otherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("UHand::EndOverlap with object: %s"), *(otherActor->GetName()));
	m_overlappedInteractable = NULL;
	m_overlappedInterComp = NULL;
}

/******************************************************************************/
void UHand::UseHand()
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
					UE_LOG(LogTemp, Log, TEXT("UHand::UseHand  Must turn the lever"));
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
							UE_LOG(LogTemp, Log, TEXT("UHand::UseHand  %s can't fit here"), *(m_pickupInHand->GetName()));
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
void UHand::TranslateUp(void)
{
	FVector curr_loc = m_savedHandSceneComponent->RelativeLocation;
	curr_loc.Z++;
	m_savedHandSceneComponent->RelativeLocation = curr_loc;
}

/******************************************************************************/
void UHand::TranslateDown(void)
{
	FVector curr_loc = m_savedHandSceneComponent->RelativeLocation;
	curr_loc.Z--;
	m_savedHandSceneComponent->RelativeLocation = curr_loc;
}
