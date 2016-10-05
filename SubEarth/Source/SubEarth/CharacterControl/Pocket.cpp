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
	m_objectCollider->bGenerateOverlapEvents = true;

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
	APickup* pickup = NULL;

	if (!m_isPocketEmpty && m_pickupInPocket != NULL)
	{
		pickup = m_pickupInPocket;
		pickup->DetachRootComponentFromParent();
		pickup->SetDefaultInHandOrientation();
		pickup->SetActorEnableCollision(true);

		m_pickupInPocket = NULL;
		m_isPocketEmpty = true;

		UE_LOG(LogTemp, Log, TEXT("Took %s out of pocket"), *pickup->GetName());
	}

	return pickup;
}

/******************************************************************************/
void UPocket::PlaceItemInPocket(APickup* pickup)
{
	if (m_isPocketEmpty)
	{
		m_pickupInPocket = pickup;
		m_isPocketEmpty = false;

		pickup->AttachToComponent(m_objectRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		pickup->SetDefaultWorldOrientation(); // TODO this create orientation for "In Pocket"
		pickup->SetActorEnableCollision(false);


		UE_LOG(LogTemp, Log, TEXT("Placed %s in pocket"), *pickup->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add %s to the pocket when the pocket is not empty!"), *pickup->GetName());
	}
}

/******************************************************************************/
FString UPocket::GetNameOfPickupInPocket(void)
{
	FString str = "EMPTY";

	if (m_pickupInPocket != NULL)
	{
		str = m_pickupInPocket->GetName();
	}

	return str;
}
