// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AFlashlight : public APickup
{
	GENERATED_BODY()
	
public:
	AFlashlight();

	// Inherited. See parent for description
	virtual void ExecuteAction1(void) override;
	virtual void ExecuteAction2(void) override;
	virtual void ExecuteAction3(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FlashLightComponent, meta = (AllowPrivateAccess = "true"))
		class USpotLightComponent* m_light;

};
