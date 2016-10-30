// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterControl/InteractableComponent.h"
#include "Objects/Interactable.h"
#include "Objects/Pickup.h"
#include "CharacterControl/PocketComponent.h"
#include "MotionControllerComponent.h"
#include "Objects/OxygenTank.h"
#include "HandComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API UHandComponent : public UInteractableComponent
{
	GENERATED_BODY()
	
public:

	UHandComponent();

	// The primary action for the door is to open if it is unlocked.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	virtual void ExecuteActionForTick(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PressButton1(void);
	void PressButton2(void);
	void PressButton3(void);
	void PressButton4(void);
	
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

	void UseHand();

	// On occassion a pickup or an interactable will require that you hold down the 
	// trigger and move your hand to interact with it. In these situations, the left
	// and right hand toggle grab will latch the hand to the object, and this function
	// will clear the latch.
	void ReleaseHand(void);

	// Used to move the right hand up and down when in PC mode
	void TranslateUp(void);
	void TranslateDown(void);

	UBoxComponent* m_savedCollider;

	void SetRelative3DScaleOnMesh(FVector scale);

private:

	void LatchHandToInteractable(AInteractable* interactable);
	void PickupObject(APickup* pickup_obj);
	void DropObject(void);

	/* The object that the hand collidor is overlapping */
	AInteractable* m_overlappedInteractable;
	UInteractableComponent* m_overlappedInterComp;

	/* The current object in the hand. NULL if hand is empty */
	APickup* m_pickupInHand;

	AInteractable* m_latchedInteractable;

	FVector m_lastLatchedLocation;
	FRotator m_lastLatchedRotation;

	bool m_isHandEmpty;
	bool m_isHandLatched;
};
