// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "InteractableComponent.h"

/******************************************************************************/
UInteractableComponent::UInteractableComponent()
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

	// TODO may or may not need this
	m_objectCollider->bGenerateOverlapEvents = true;
}

/******************************************************************************/
USceneComponent* UInteractableComponent::GetObjectRoot(void)
{
	return m_objectRoot;
}

/******************************************************************************/
void UInteractableComponent::SetRelativePosition(FVector position)
{
	m_objectRoot->RelativeLocation = position;
}

/******************************************************************************/
UInteractableComponent::InteractableComponent_e UInteractableComponent::GetInteractableComponentType(void)
{
	return m_interactableComponentType;
}

/******************************************************************************/
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("UInteractableComponent BeginPlay started"));
}

/******************************************************************************/
void UInteractableComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

