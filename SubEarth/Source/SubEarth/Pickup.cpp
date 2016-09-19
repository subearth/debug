// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Pickup.h"

#include "SubEarthCharacter.h"
#include "Hand.h"

APickup::APickup()
{
	



}

void APickup::CollisionOccured(UPrimitiveComponent* overlappedComponent,
	                           AActor* otherActor,
	                           UPrimitiveComponent* otherComponent,
	                           int32 otherBodyIndex,
	                           bool bFromSweep,
	                           const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("APickup::CollisionOccured  A collision occured with a pickup object"));

	if (otherActor->IsA(ASubEarthCharacter::StaticClass())) // Type check before casting
	{
		ASubEarthCharacter* character = (ASubEarthCharacter*)otherActor;

		// We only want to pick up the obect iff the hand overlapped the pickup
		// objects collider, AND the user presses the button to pick up the object.

		UHand* hand = NULL;

		// Is it the left or right hand?
		if (otherComponent == character->leftHand->handCollider)
		{
			hand = character->leftHand;
			UE_LOG(LogTemp, Log, TEXT("LEFT HAND"));
		}
		else if (otherComponent == character->rightHand->handCollider)
		{
			hand = character->rightHand;
			UE_LOG(LogTemp, Log, TEXT("RIGHT HAND"));
		}

		if (hand != NULL)
		{
			if (hand->IsGrabbing()) // Is the pickup button pressed
			{
				if (hand->IsHandEmpty())
				{
					hand->PickupObject(this);
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("hand not empty"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Not grabbing"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("APickup::CollisionOccured Not a hand component"));
		}
	}
}



