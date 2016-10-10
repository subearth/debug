// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterControl/InteractableComponent.h"
#include "Objects/Pickup.h"
#include "PocketComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API UPocketComponent : public UInteractableComponent
{
	GENERATED_BODY()
	
public:

	UPocketComponent();

	// The primary action for the door is to open if it is unlocked.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	bool IsPocketEmpty();
	APickup* TakeItemOutOfPocket(void);
	void PlaceItemInPocket(APickup* pickup);

	FString GetNameOfPickupInPocket(void);

private:

	/* The current object in the pocket. NULL if pocket is empty */
	APickup* m_pickupInPocket;

	bool m_isPocketEmpty;
	
};
