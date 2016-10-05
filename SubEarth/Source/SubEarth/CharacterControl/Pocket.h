// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Objects/Pickup.h"

#include "Pocket.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBEARTH_API UPocket : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPocket();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void SetRelativePosition(FVector position);

	bool IsPocketEmpty();
	APickup* TakeItemOutOfPocket(void);
	void PlaceItemInPocket(APickup* pickup);

	USceneComponent* GetObjectRoot(void);

	FString GetNameOfPickupInPocket(void);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_objectCollider;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_objectRoot;

	// Static mesh for the object being picked up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_objectMesh;



	USceneComponent* m_savedObjectRoot;

	/* The current object in the pocket. NULL if pocket is empty */
	APickup* m_pickupInPocket;

	bool m_isPocketEmpty;
		
};
