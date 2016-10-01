// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "CharacterControl/Hand.h"
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
	handSceneComponent = CreateDefaultSubobject<USceneComponent>(FName(*RootName));
	m_savedHandSceneComponent = handSceneComponent;

	FString MeshName = HandName + "Mesh";
	handMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));	
	handMesh->SetupAttachment(handSceneComponent);

	FString ColliderName = HandName + "Collider";
	handCollider = CreateDefaultSubobject<UCapsuleComponent>(FName(*ColliderName));
	handCollider->bGenerateOverlapEvents = true;
	handCollider->OnComponentBeginOverlap.AddDynamic(this, &UHand::BeginOverlap);
	handCollider->OnComponentEndOverlap.AddDynamic(this, &UHand::EndOverlap);
	handCollider->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	handCollider->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
	handCollider->SetupAttachment(handSceneComponent);
	
	// Start off holding nothing.
	m_isHandEmpty = true;
	m_pickupInHand = NULL;
	m_overlappedInteractable = NULL;
	
	//InHandActor = NULL;
	//CollidedActor = NULL;
}

// Called when the game starts
void UHand::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/******************************************************************************/
void UHand::PickupObject(APickup* pickup_obj)
{
	// Drop what's in our hand and pick up the other object
	if (!m_isHandEmpty)
	{
		DropObject();
	}

	pickup_obj->AttachToComponent(m_savedHandSceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	pickup_obj->SetDefaultInHandOrientation();

	m_pickupInHand = pickup_obj;
	m_overlappedInteractable = NULL; // We picked it up, therefore it is no longer overlapping
	m_isHandEmpty = false;

	UE_LOG(LogTemp, Log, TEXT("AHand::PickupObject %s"), *(m_pickupInHand->GetName()));
}

/******************************************************************************/
void UHand::DropObject()
{
	UE_LOG(LogTemp, Log, TEXT("AHand::DropObject %s"), *(m_pickupInHand->GetName()));
	m_pickupInHand->SetDefaultWorldOrientation();
	m_pickupInHand->DetachRootComponentFromParent();
	m_overlappedInteractable = (AInteractable*)m_pickupInHand; // We just dropped it, therefore it is currently overlapping
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
	if (m_pickupInHand != NULL)
	{
		m_pickupInHand->ExecuteAction1();
	}
}

/******************************************************************************/
void UHand::PressButton3(void)
{
	if (m_pickupInHand != NULL)
	{
		m_pickupInHand->ExecuteAction2();
	}
}

/******************************************************************************/
void UHand::PressButton4(void)
{
	if (m_pickupInHand != NULL)
	{
		m_pickupInHand->ExecuteAction3();
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
	UE_LOG(LogTemp, Log, TEXT("UHand::BeginOverlap with object: %s"), *(otherActor->GetName()));

	if (otherActor->IsA(AInteractable::StaticClass())) // Type check before casting
	{
		m_overlappedInteractable = (AInteractable*)otherActor;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UHand::BeginOverlap object %s is not an interactable object"), *(otherActor->GetName()));
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
}

/******************************************************************************/
void UHand::UseHand()
{
	// Is the hand overlapping something we need to interact with?
	if (m_overlappedInteractable != NULL)
	{
		if (m_overlappedInteractable->IsA(APickup::StaticClass())) 
		{			
			PickupObject((APickup*)m_overlappedInteractable);
		}
		else if (m_overlappedInteractable->IsA(AInteractable::StaticClass()))
		{
			// Interact with the object. This could be like the "enter" key
		}
	}
	// If we were holding something, drop it.
	else if (!m_isHandEmpty)
	{
		DropObject();
	}
}
