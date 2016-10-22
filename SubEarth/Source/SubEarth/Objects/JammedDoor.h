// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Interactable.h"
#include "Objects/DoorLever.h"
#include "JammedDoor.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AJammedDoor : public AInteractable
{
	GENERATED_BODY()
	
public:

	AJammedDoor();

	// The primary action for the door is to open if it is unlocked.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	void ToggleLock(void);
	bool IsLeverInPlace(void);

private:

	ADoorLever* m_lever;

	bool m_isLocked;
};
