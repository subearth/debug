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

	// A pickup object has three possible actions
	virtual void ExecuteAction1(void) PURE_VIRTUAL(APickup::ExecuteAction1, );
	virtual void ExecuteAction2(void) PURE_VIRTUAL(APickup::ExecuteAction2, );
	virtual void ExecuteAction3(void) PURE_VIRTUAL(APickup::ExecuteAction3, );

/*
	UFUNCTION()
		void OnPlayerHandOverlap(UPrimitiveComponent* overlappedComponent, class AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayerOverlapExit(UPrimitiveComponent * overlappedComponent, class AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex);
*/
};
