// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "InteractableComponent.h"

/******************************************************************************/
UInteractableComponent::UInteractableComponent()
{
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

	// Enable the tick call back, but start with it disabled
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

/******************************************************************************/
USceneComponent* UInteractableComponent::GetObjectRoot(void)
{
	return m_savedObjectRoot;
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
void UInteractableComponent::EnableTick(void)
{
	SetComponentTickEnabled(true);
}

/******************************************************************************/
void UInteractableComponent::DisableTick(void)
{
	SetComponentTickEnabled(false);
}

/******************************************************************************/
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ExecuteActionForTick(DeltaTime, TickType, ThisTickFunction);
}

/******************************************************************************/
void UInteractableComponent::SetRelativePosition(FVector position)
{
	m_objectRoot->RelativeLocation = position;
}
