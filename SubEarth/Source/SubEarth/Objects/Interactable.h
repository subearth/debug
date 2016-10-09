// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS(abstract)
class SUBEARTH_API AInteractable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	USceneComponent* GetObjectRoot();

protected:

	UPROPERTY(EditAnywhere)
		USceneComponent* m_objectRoot;

	// Static mesh for the object being picked up
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_objectMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* m_objectCollider;
};
