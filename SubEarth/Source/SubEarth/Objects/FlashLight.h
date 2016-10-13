// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "FlashLight.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AFlashLight : public APickup
{
	GENERATED_BODY()
	
public:

	AFlashLight();

	// Inherited. See parent for description
	virtual void ExecuteAction1(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction2(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction3(AInteractable* interactable = NULL) override;

	// Inherited. See parent for description
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;



private:
	// Light component:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpotLightComponent* SpotLight;
	
	FString m_spotLightName;
	float m_minAngle;
	float m_deltaAngle;
	float m_minRadius;
	float m_deltaRadius;
	float m_zoomPercent;
};
