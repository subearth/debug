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


/* Keep these. We will end up needed OnPlayerHandOverlap or similar function
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