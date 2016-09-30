// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "CharacterControl/Hand.h"

#include "Objects/Interactable.h"
#include "Objects/Pickup.h"
#include <string> 

// Sets default values for this component's properties
UHand::UHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	FString HandName = GetName();

	FString RootName = HandName + "Root";
	//handSceneComponent = this->CreateDefaultSubobject<USceneComponent>(FName(*RootName));
	handSceneComponent = CreateDefaultSubobject<USceneComponent>(FName(*RootName));
	savedHandSceneComponent = handSceneComponent;

	FString MeshName = HandName + "Mesh";
	//handMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));
	handMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));	
	handMesh->SetupAttachment(handSceneComponent);

	FString ColliderName = HandName + "Collider";
	//handCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	handCollider = CreateDefaultSubobject<UCapsuleComponent>(FName(*ColliderName));
	handCollider->bGenerateOverlapEvents = true;
	handCollider->OnComponentBeginOverlap.AddDynamic(this, &UHand::BeginOverlap);
	handCollider->OnComponentEndOverlap.AddDynamic(this, &UHand::EndOverlap);
	handCollider->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	handCollider->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
	handCollider->SetupAttachment(handSceneComponent);
	
	
	isHandEmpty = true;

	// Start off holding nothing.
	pickupObject = NULL;
	
	InHandActor = NULL;
	CollidedActor = NULL;
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
void UHand::PickupObject()
{
	APickup* pickup_obj = (APickup*)CollidedActor;
	// If you have an object in your hand, drop it so you can pick up the new object
	/*if (!isHandEmpty)
	{
		DropObject();
	}

	isHandEmpty = false;
	pickupObject = object;*/
	//CollidedActor->GetRootComponent()->SetupAttachment(savedHandSceneComponent);
	
	//pickup_obj->DetachRootComponentFromParent();
	
	//pickup_obj->AttachToComponent(handSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//pickup_obj->AttachToComponent(savedHandSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//pickup_obj->GetRootComponent()->RelativeLocation = FVector(0, 0, 0);
	
	//CollidedActor->SetActorLocation(FVector::ZeroVector);
	//CollidedActor->DetachRootComponentFromParent();
	//CollidedActor->AttachRootComponentTo(handSceneComponent);
	CollidedActor->AttachToComponent(savedHandSceneComponent,FAttachmentTransformRules::SnapToTargetIncludingScale);
	//CollidedActor->GetRootComponent()->RelativeLocation = FVector::ZeroVector;

	InHandActor = CollidedActor;
	CollidedActor = NULL;
	//object->GetObjectRoot()->SetupAttachment(savedHandSceneComponent);
	UE_LOG(LogTemp, Log, TEXT("AHand::PickupObject Object picked up"));
}

/******************************************************************************/
void UHand::DropObject()
{
	//isHandEmpty = true;
	//pickupObject = NULL;
	InHandActor->DetachRootComponentFromParent();
	//InHandActor->Destroy();
	//InHandActor->AttachToComponent(, FAttachmentTransformRules::KeepRelativeTransform);
	InHandActor = NULL;

	
	//pickup_obj->GetRootComponent()->RelativeLocation = FVector(0, 0, 0);
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

/******************************************************************************/
void UHand::BeginOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("UHand::CollisionOccured  A collision occured with a interactable object"));

	CollidedActor = otherActor;

	//if (otherActor->IsA(APickup::StaticClass())) // Type check before casting
	//{
	//	APickup* pickup_obj = (APickup*)otherActor;

	//	// We only want to pick up the object iff the hand overlapped the pickup
	//	// objects collider, AND the user presses the button to pick up the object.

	//	if (IsGrabbing()) // Is the pickup button pressed
	//	{
	//		if (IsHandEmpty())
	//		{
	//			PickupObject(pickup_obj);
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("hand not empty"));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Not grabbing"));
	//	}
	//}
}

/******************************************************************************/

void UHand::EndOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("UHand::CollisionOccured  A collision occured with a interactable object"));

	CollidedActor = NULL;

	//if (otherActor->IsA(APickup::StaticClass())) // Type check before casting
	//{
	//	APickup* pickup_obj = (APickup*)otherActor;

	//	// We only want to pick up the object iff the hand overlapped the pickup
	//	// objects collider, AND the user presses the button to pick up the object.

	//	if (IsGrabbing()) // Is the pickup button pressed
	//	{
	//		if (IsHandEmpty())
	//		{
	//			PickupObject(pickup_obj);
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("hand not empty"));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Not grabbing"));
	//	}
	//}
}

void UHand::UseHand()
{
	// Drop what's in our hand:
	if (InHandActor != NULL)
	{
		DropObject();
	}
	// Try to pickup what we are colliding with:
	else if (CollidedActor != NULL)
	{
		// Make sure it is a pickup...
		if (CollidedActor->IsA(APickup::StaticClass())) // Type check before casting
		{
			PickupObject();
		}
	}
}