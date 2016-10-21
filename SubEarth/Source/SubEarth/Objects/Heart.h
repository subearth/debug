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
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;	
};
