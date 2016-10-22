// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "DoorLever.generated.h"

class AJammedDoor;
/**
 * 
 */
UCLASS()
class SUBEARTH_API ADoorLever : public APickup
{
	GENERATED_BODY()

public:

	ADoorLever();

	// Inherited. See parent for description
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	// Inherited. See parent for description
	virtual void ExecuteAction1(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction2(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction3(AInteractable* interactable = NULL) override;

	// Inherited. See parent for description
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;

	void SetupAttachToDoorParams(AJammedDoor* door);
	bool IsAttachedToDoor(void);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_leftCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_rightCollider;

	bool m_leverInDoor;
	AJammedDoor* m_doorAttachedTo;

};
