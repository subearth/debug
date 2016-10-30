// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Pickup.h"
#include "CharacterControl/InteractableComponent.h"
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
	virtual void ExecuteAction1(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction2(AInteractable* interactable = NULL) override;
	virtual void ExecuteAction3(AInteractable* interactable = NULL) override;

	// Inherited. See parent for description
	virtual void SetDefaultInHandOrientation(void) override;

	// Inherited. See parent for description
	virtual void SetDefaultWorldOrientation(void) override;

	void SetupAttachToDoorParams(AJammedDoor* door);
	bool IsAttachedToDoor(void);

	virtual void UpdateLocAndRot(FVector delta_loc, FRotator delta_rot, FString name) override;

	UFUNCTION()
		void LeftColliderBeginOverlap(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void RightColliderBeginOverlap(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void LeftColliderEndOverlap(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex);

	UFUNCTION()
		void RightColliderEndOverlap(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_leftCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_rightCollider;

	
	AJammedDoor* m_doorAttachedTo;
	UInteractableComponent* m_leftHand;
	UInteractableComponent* m_rightHand;

	float m_approxRadius;

	bool m_leverInDoor;
	bool m_leftColliderGrabbed;
	bool m_rightColliderGrabbed;
};
