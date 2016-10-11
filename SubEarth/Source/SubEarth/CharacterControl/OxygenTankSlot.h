// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterControl/InteractableComponent.h"
#include "Objects/Pickup.h"
#include "OxygenTankSlot.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API UOxygenTankSlot : public UInteractableComponent
{
	GENERATED_BODY()
	
public:

	UOxygenTankSlot();

	// The primary action for the door is to open if it is unlocked.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	bool IsEmpty(void);
	APickup* TakeTankFromSlot(void);
	void PlaceTankInSlot(APickup* pickup);
	void DropTankInSlot(void);
	
	float GetTankInitialLevel(void);
	float GetTankCurrentLevel(void);
	void SetTankCurrentLevel(float value);

private:
	APickup* m_tankInSlot;
};
