// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Pocket.h"

/******************************************************************************/
UPocket::UPocket()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	FString name = GetName();

	FString RootName = name + "Root";
	m_objectRoot = CreateDefaultSubobject<USceneComponent>(*RootName);
	m_savedObjectRoot = m_objectRoot;

	FString MeshName = name + "Mesh";
	m_objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));
	m_objectMesh->SetupAttachment(m_objectRoot);

	FString ColliderName = name + "Collider";
	m_objectCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_objectCollider->SetupAttachment(m_objectRoot);
	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));

	m_objectCollider->bHiddenInGame = false;

	m_pickupInPocket = NULL;
	m_isPocketEmpty = true;
}


/******************************************************************************/
void UPocket::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

/******************************************************************************/
USceneComponent* UPocket::GetObjectRoot()
{
	return m_objectRoot;
}

/******************************************************************************/
void UPocket::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

/******************************************************************************/
void UPocket::SetRelativePosition(FVector position)
{
	m_objectRoot->RelativeLocation = position;
}

/******************************************************************************/
bool UPocket::IsPocketEmpty()
{
	return m_isPocketEmpty;
}

/******************************************************************************/
APickup* UPocket::TakeItemOutOfPocket(void)
{
	APickup* pickup = m_pickupInPocket;
	m_pickupInPocket = NULL;
	m_isPocketEmpty = true;

	return pickup;
}

/******************************************************************************/
void UPocket::PlaceItemInPocket(APickup* pickup)
{
	m_pickupInPocket = pickup;
	m_isPocketEmpty = false;
}
