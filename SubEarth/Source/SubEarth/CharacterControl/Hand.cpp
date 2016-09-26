// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "CharacterControl/Hand.h"


// Sets default values for this component's properties
UHand::UHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	handSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HandRoot"));
	savedHandSceneComponent = handSceneComponent;

	handMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandMesh"));
	handMesh->SetupAttachment(handSceneComponent);

	handCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HandCollider"));
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

	m_controller->SetupAttachment(object->GetRootComponent());

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