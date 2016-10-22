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

	enum Pickup_e
	{
		COLOR_CHANGING_ORB,
		GENERIC_KEY,
		OXYGEN_TANK,
		DOOR_LEVER
	};

	enum FloatMode_e
	{
		NONE,
		SINK,
		FLOAT,
		BOB
	};

	APickup();

	// Inherited. See parent for description
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	// A pickup object has three possible actions
	virtual void ExecuteAction1(AInteractable* interactable = NULL) PURE_VIRTUAL(APickup::ExecuteAction1, );
	virtual void ExecuteAction2(AInteractable* interactable = NULL) PURE_VIRTUAL(APickup::ExecuteAction2, );
	virtual void ExecuteAction3(AInteractable* interactable = NULL) PURE_VIRTUAL(APickup::ExecuteAction3, );

	/** Returns the default orientation of the object when it is placed in the hand */
	virtual void SetDefaultInHandOrientation(void);

	/** Returns the default orientation of the object when it is placed in the world */
	virtual void SetDefaultWorldOrientation(void);

	Pickup_e GetPickupType(void);

	// For the falling:
	// Only called if the derived call enables animation
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* overlappedComponent,
		AActor* otherActor,
		UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* overlappedComponent,
		AActor* otherActor,
		UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex);

protected:

	Pickup_e m_pickupType;
	void ExecutePhysics(float delta_time);
	FloatMode_e m_floatMode;
	float m_floatSpeed;
	float m_floatRange;
	float m_floatDisplacement;
	float m_floatDirection;
	int m_floatRotate;
	bool m_isFloating;
	AActor* m_firstTouched;
};
