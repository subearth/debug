// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Objects/Interactable.h"
#include "Objects/Pickup.h"
#include "CharacterControl/Pocket.h"
#include "MotionControllerComponent.h"

#include "Hand.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SUBEARTH_API UHand : public UActorComponent
{
	GENERATED_BODY()

public:

	UHand();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* handSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* handMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* handCollider;

	USceneComponent* GetHandSceneComponent(void) { return m_savedHandSceneComponent; }

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

private:

	void PickupObject(APickup* pickup_obj);
	void DropObject(void);

	/* The object that the hand collidor is overlapping */
	AInteractable* m_overlappedInteractable;
	UPocket* m_overlappedPocket;

	/* The current object in the hand. NULL if hand is empty */
	APickup* m_pickupInHand;
	
	USceneComponent* m_savedHandSceneComponent;
	
	// The hand can only interact with interactable objects. Maybe these were added
	// so that the hand could push off a wall? 
	//AActor* InHandActor;
	//AActor* CollidedActor;

	bool m_isHandEmpty;
};
