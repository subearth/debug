// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Pickup.h"

#include "SubEarthCharacter.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = pickupRoot;

	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	pickupMesh->SetupAttachment(pickupRoot);

	pickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	pickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	pickupBox->bGenerateOverlapEvents = true;
	pickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerHandOverlap);
	pickupBox->SetupAttachment(pickupRoot);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("APickup started"));
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APickup::OnPlayerHandOverlap(UPrimitiveComponent * overlappedComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/* NOTE
	This code is not complete. Feel free to work on it if you have the time.  Essentially, we need to 
	be able to pick up an object iff the hand and object overlap AND the user presses the button to 
	pick up the object.  */

	// TODO need to change to something like if (sub earth character hand).  
	if (otherActor->IsA(ASubEarthCharacter::StaticClass()))
	{
		// TODO, then update this to be casted as the correct hand (left or right)
		// For right now, if our character mesh collides with the pick object AND our left hand is free,
		// "pickup the object"
		ASubEarthCharacter* c = (ASubEarthCharacter*)otherActor;

		if (c->IsHandEmpty((int)ASubEarthCharacter::LEFT_HAND))
		{
			Destroy(); // TODO Place object in hand
			UE_LOG(LogTemp, Log, TEXT("Object destroyed"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Left hand not empty"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not a ASubEarthCharacter object"));
	}
}

