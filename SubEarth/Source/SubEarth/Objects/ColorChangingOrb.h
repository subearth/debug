// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "ColorChangingOrb.generated.h"

/**
*
*/
UCLASS()
class SUBEARTH_API AColorChangingOrb : public APickup
{
	GENERATED_BODY()

public:

	AColorChangingOrb();

	// Inherited. See parent for description
	virtual void ExecuteAction1(void) override;
	virtual void ExecuteAction2(void) override;
	virtual void ExecuteAction3(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;

};
