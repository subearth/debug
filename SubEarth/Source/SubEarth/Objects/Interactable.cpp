// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Interactable.h"

#include "CharacterControl/SubEarthCharacter.h"

// Sets default values
AInteractable::AInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString name = GetName();

	FString RootName = name + "Root";
	m_objectRoot = CreateDefaultSubobject<USceneComponent>(*RootName);
	RootComponent = m_objectRoot;

	FString MeshName = name + "Mesh";
	m_objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));
	m_objectMesh->SetupAttachment(m_objectRoot);

	FString ColliderName = name + "Collider";
	m_objectCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_objectCollider->SetupAttachment(m_objectRoot);
}

USceneComponent* AInteractable::GetObjectRoot()
{
	return m_objectRoot;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AInteractable BeginPlay started"));
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

