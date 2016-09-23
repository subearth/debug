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

protected:

	UPROPERTY(EditAnywhere)
		USceneComponent* objectRoot;

	// Static mesh for the object being picked up
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* objectMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* objectCollider;

	UFUNCTION()
		void OnPlayerHandOverlap(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	virtual void CollisionOccured(UPrimitiveComponent* overlappedComponent,
		AActor* otherActor,
		UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) PURE_VIRTUAL(AInteractable::CollisionOccured, );
};
