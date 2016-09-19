// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Pickup.h"

#include "Hand.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBEARTH_API UHand : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHand();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USceneComponent* handSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* handMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* handCollider;

	USceneComponent* GetHandSceneComponent(void) { return handSceneComponent; }

	void PickupObject(APickup* object);
	void DropObject(void);

	bool IsHandEmpty(void);

	/** When the user presses the button to pick up the object, this function
	needs to be called
	@param grabbing Set true if button is depressed, false otherwise */
	void SetGrabbing(bool grabbing);

	bool IsGrabbing(void);

	void PressButton1(void);
	void PressButton2(void);
	void PressButton3(void);
	void PressButton4(void);

private:

	/* The object in the hand */
	APickup* pickupObject;

	bool isHandEmpty;
	bool isGrabbing;  // true if in the process of grabbing an object
};
