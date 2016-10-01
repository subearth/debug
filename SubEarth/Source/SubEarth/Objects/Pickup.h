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

	/** Returns the default orientation of the object when it is placed in the hand */
	virtual void SetDefaultInHandOrientation(void);

	/** Returns the default orientation of the object when it is placed in the world */
	virtual void SetDefaultWorldOrientation(void);
};
