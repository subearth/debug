// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Interactable.h"

#include "CharacterControl/SubEarthCharacter.h"

// Sets default values
AInteractable::AInteractable()
{
	//Super::AActor(); // Call parents constructor

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objectRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ObjectRoot"));
	RootComponent = objectRoot;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	objectMesh->SetupAttachment(objectRoot);

	objectCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ObjectCollider"));
	objectCollider->SetupAttachment(objectRoot);
}

USceneComponent* AInteractable::GetObjectRoot()
{
	return objectRoot;
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

