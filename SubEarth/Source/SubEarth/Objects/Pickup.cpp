// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Pickup.h"

#include "CharacterControl/SubEarthCharacter.h"
#include "CharacterControl/Hand.h"

APickup::APickup()
{
	/*
	pickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = pickupRoot;

	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	pickupMesh->SetupAttachment(pickupRoot);

	pickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	pickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	pickupBox->bGenerateOverlapEvents = true;
	pickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerHandOverlap);
	pickupBox->OnComponentEndOverlap.AddDynamic(this, &APickup::OnPlayerOverlapExit);
	pickupBox->SetupAttachment(pickupRoot);
	*/
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
		if (otherComponent == character->m_leftHand->handCollider)
		{
			hand = character->m_leftHand;
			UE_LOG(LogTemp, Log, TEXT("LEFT HAND"));
		}
		else if (otherComponent == character->m_rightHand->handCollider)
		{
			hand = character->m_rightHand;
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

/*
void APickup::PickupItem()
{
MyPlayerController->ShowInventory.Add(*pickupName);
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Added to inventory. Press I to see the list"));
Destroy();
}
*/

/*
void APickup::OnPlayerHandOverlap(UPrimitiveComponent * overlappedComponent, class AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
bItemIsWithinRange = true;
GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString::Printf(TEXT("Press T to pickup %s "), *pickupName));
GetPlayer(otherActor);
}*/

/*
void APickup::OnPlayerOverlapExit(UPrimitiveComponent * overlappedComponent, class AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex)
{
bItemIsWithinRange = false;
}
*/