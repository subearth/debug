// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "Heart.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AHeart : public APickup
{
	GENERATED_BODY()
public:

	AHeart();

	// Inherited. See parent for description
	virtual void ExecuteAction1(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction2(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction3(AInteractable* interactable = NULL) override;

	// Inherited. See parent for description
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;
};
