// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Interactable.h"
#include "GenericDoor.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AGenericDoor : public AInteractable
{
	GENERATED_BODY()
	
	
public:

	AGenericDoor();

	// Inherited. See parent for description
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;
	
	void ToggleLock(void);
	bool IsDoorLocked(void);

private:

	bool m_isLocked;
};
