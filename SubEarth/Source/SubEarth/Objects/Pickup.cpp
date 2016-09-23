// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Pickup.h"

#include "CharacterControl/SubEarthCharacter.h"
#include "CharacterControl/Hand.h"

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
	pickupBox->OnComponentEndOverlap.AddDynamic(this, &APickup::OnPlayerOverlapExit);
	pickupBox->SetupAttachment(pickupRoot);



}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("APickup started"));

}

void APickup::PickupItem()
{
	MyPlayerController->ShowInventory.Add(*pickupName);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Added to inventory. Press I to see the list"));
	Destroy();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyPlayerController != NULL) // Null check player controller
	{
		if (MyPlayerController->bIsLeftPickingUp && bItemIsWithinRange)
		{
			PickupItem();
		}
		else if (MyPlayerController->bIsRightPickingUp && bItemIsWithinRange)
		{
			PickupItem();
		}
	}

}

void APickup::GetPlayer(AActor* Player)
{
	MyPlayerController = Cast<ASubEarthCharacter>(Player);

}

void APickup::OnPlayerHandOverlap(UPrimitiveComponent * overlappedComponent, class AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/* NOTE
	This code is not complete. Feel free to work on it if you have the time.  Essentially, we need to
	be able to pick up an object iff the hand and object overlap AND the user presses the button to
	pick up the object.  */

	// TODO need to change to something like if (sub earth character hand).  
	//if (otherActor->IsA(ASubEarthCharacter::StaticClass()))
	//{
	//	 TODO, then update this to be casted as the correct hand (left or right)
	//	 For right now, if our character mesh collides with the pick object AND our left hand is free,
	//	 "pickup the object"
	//	ASubEarthCharacter* c = (ASubEarthCharacter*)otherActor;

	//	if (c->IsHandEmpty((int)ASubEarthCharacter::LEFT_HAND))
	//	{
	//		bItemIsWithinRange = true;

	//		Destroy(); // TODO Place object in hand
	//		UE_LOG(LogTemp, Log, TEXT("Object destroyed"));
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Left hand not empty"));
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Not a ASubEarthCharacter object"));
	//}


	/*Onlu for one handed pickup and inventory to test*/
	bItemIsWithinRange = true;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString::Printf(TEXT("Press T to pickup %s "), *pickupName));
	GetPlayer(otherActor);
}

void APickup::OnPlayerOverlapExit(UPrimitiveComponent * overlappedComponent, class AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex)
{
	bItemIsWithinRange = false;
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

