// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Interactable.h"
#include "Pickup.generated.h"

/**
*
*/
UCLASS(abstract)
class SUBEARTH_API APickup : public AInteractable
{
	GENERATED_BODY()

public:

	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void CollisionOccured(UPrimitiveComponent* overlappedComponent,
		AActor* otherActor,
		UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	// A pickup object has three possible actions
	virtual void ExecuteAction1(void) PURE_VIRTUAL(APickup::ExecuteAction1, );
	virtual void ExecuteAction2(void) PURE_VIRTUAL(APickup::ExecuteAction2, );
	virtual void ExecuteAction3(void) PURE_VIRTUAL(APickup::ExecuteAction3, );

	UPROPERTY(EditAnywhere)
		USceneComponent* pickupRoot;

	// Static mesh for the object being picked up
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* pickupMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* pickupBox;

	class ASubEarthCharacter * MyPlayerController; //Can be initialised inside Sean's if-else ladder

	UPROPERTY(EditAnywhere)
		FString pickupName = FString(TEXT(""));

	void PickupItem();

	void GetPlayer(AActor * Player);

	bool bItemIsWithinRange = false;

	UFUNCTION()
		void OnPlayerHandOverlap(UPrimitiveComponent* overlappedComponent, class AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayerOverlapExit(UPrimitiveComponent * overlappedComponent, class AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex);
};
