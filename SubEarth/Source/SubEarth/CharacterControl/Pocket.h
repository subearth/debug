// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Interactable.h"
#include "Objects/Pickup.h"
#include "Pocket.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API APocket : public AInteractable
{
	GENERATED_BODY()

public:

	APocket();

	void SetRelativePosition(FVector position);

	bool IsPocketEmpty();
	APickup* TakeItemOutOfPocket(void);
	void PlaceItemInPocket(APickup* pickup);

private:	


	/* The current object in the pocket. NULL if pocket is empty */
	APickup* m_pickupInPocket;

	bool m_isPocketEmpty;
};
