// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "OxygenTank.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AOxygenTank : public APickup
{
	GENERATED_BODY()
	
public:

	AOxygenTank();
	void GetOxygenTank(void);
	bool IsOxygenTankPickedUp ;
	
	
};
