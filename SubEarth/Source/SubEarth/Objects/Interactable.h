// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class APickup;

UCLASS(abstract)
class SUBEARTH_API AInteractable : public AActor
{
	GENERATED_BODY()

public:

	enum Interactable_e
	{
		PICKUP_OBJECT,
		GENERIC_DOOR,
		TOOL_BOX
	};

	// Sets default values for this actor's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;

	USceneComponent* GetObjectRoot(void);

	Interactable_e GetInteractableType(void);

	// The primary action for an interactable gets called when the user hand is overlapped
	// with the interactable and the user pulls the trigger.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) PURE_VIRTUAL(AInteractable::ExecutePrimaryAction, );

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InteractableComponent", meta=(AllowPrivateAccess="true"))
		class USceneComponent* m_objectRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InteractableComponent", meta=(AllowPrivateAccess="true"))
		class UStaticMeshComponent* m_objectMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InteractableComponent", meta=(AllowPrivateAccess="true"))
		class UBoxComponent* m_objectCollider;
	Interactable_e m_interactableType;
};
