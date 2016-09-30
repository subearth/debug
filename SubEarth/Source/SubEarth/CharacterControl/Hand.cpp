// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "CharacterControl/Hand.h"

#include "Objects/Interactable.h"
#include "Objects/Pickup.h"
#include <string> 

// Sets default values for this component's properties
UHand::UHand()
{
	// Unable to figure out how to pass FName's into the constructor. May not be allowed
	// by UE4.  The following integer appending is to create unique names for the objects
	static int itr = 0;

	FString temp;

	temp = "HandRoot";
	temp.AppendInt(itr);
	FName root = FName(*temp);

	temp = "HandMesh";
	temp.AppendInt(itr);
	FName mesh = FName(*temp);

	temp = "HandCollider";
	temp.AppendInt(itr);
	FName collider = FName(*temp);

	itr++;
	

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	handSceneComponent = this->CreateDefaultSubobject<USceneComponent>(root);
	savedHandSceneComponent = handSceneComponent;

	handMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(mesh);
	handMesh->SetupAttachment(handSceneComponent);

	handCollider = this->CreateDefaultSubobject<UBoxComponent>(collider);
	handCollider->bGenerateOverlapEvents = true;
	handCollider->OnComponentBeginOverlap.AddDynamic(this, &UHand::CollisionOccured);
	handCollider->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	handCollider->SetupAttachment(handSceneComponent);

	isHandEmpty = true;

	// Start off holding nothing.
	pickupObject = NULL;
}


void UHand::SetMotionController(UMotionControllerComponent* motion_controller)
{
	m_controller = motion_controller;
}

// Called when the game starts
void UHand::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


/******************************************************************************/
void UHand::PickupObject(APickup* object)
{
	// If you have an object in your hand, drop it so you can pick up the new object
	if (!isHandEmpty)
	{
		DropObject();
	}

	isHandEmpty = false;
	pickupObject = object;

	object->DetachRootComponentFromParent();
	object->AttachToComponent(savedHandSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	object->GetRootComponent()->RelativeLocation = FVector(0, 0, 0);
	
	//object->GetObjectRoot()->SetupAttachment(savedHandSceneComponent);
	UE_LOG(LogTemp, Log, TEXT("AHand::PickupObject Object picked up"));
}

/******************************************************************************/
void UHand::DropObject()
{
	isHandEmpty = true;
	pickupObject = NULL;
	UE_LOG(LogTemp, Log, TEXT("AHand::DropObject Dropped the object"));
}

/******************************************************************************/
bool UHand::IsHandEmpty(void)
{
	return isHandEmpty;
}

/******************************************************************************/
void UHand::SetGrabbing(bool grabbing)
{
	isGrabbing = grabbing;
	UE_LOG(LogTemp, Log, TEXT("isGrabbing %d"), isGrabbing);
}

/******************************************************************************/
bool UHand::IsGrabbing(void)
{
	return isGrabbing;
}

/******************************************************************************/
void UHand::PressButton1(void)
{
	// Used for propolsion
}

/******************************************************************************/
void UHand::PressButton2(void)
{
	if (pickupObject != NULL)
	{
		pickupObject->ExecuteAction1();
	}
}

/******************************************************************************/
void UHand::PressButton3(void)
{
	if (pickupObject != NULL)
	{
		pickupObject->ExecuteAction2();
	}
}

/******************************************************************************/
void UHand::PressButton4(void)
{
	if (pickupObject != NULL)
	{
		pickupObject->ExecuteAction3();
	}
}


void UHand::CollisionOccured(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("UHand::CollisionOccured  A collision occured with a interactable object"));

	if (otherActor->IsA(APickup::StaticClass())) // Type check before casting
	{
		APickup* pickup_obj = (APickup*)otherActor;

		// We only want to pick up the obect iff the hand overlapped the pickup
		// objects collider, AND the user presses the button to pick up the object.

		if (IsGrabbing()) // Is the pickup button pressed
		{
			if (IsHandEmpty())
			{
				PickupObject(pickup_obj);
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
}