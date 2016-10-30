// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class APickup;

UCLASS(abstract)
class SUBEARTH_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	enum InteractableComponent_e
	{
		POCKET,
		OXYGEN_TANK_SLOT,
		HAND
	};

	// Sets default values for this component's properties
	UInteractableComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	USceneComponent* GetObjectRoot(void);
	void SetRelativePosition(FVector position);
	InteractableComponent_e GetInteractableComponentType(void);

	// The primary action for an interactable gets called when the user hand is overlapped
	// with the interactable and the user pulls the trigger.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) PURE_VIRTUAL(AInteractable::ExecutePrimaryAction, );

	// TODO make this private again!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_objectCollider;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_objectRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_objectMesh;
	
	void EnableTick(void);
	void DisableTick(void);

	virtual void ExecuteActionForTick(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {};

	USceneComponent* m_savedObjectRoot;

	InteractableComponent_e m_interactableComponentType;
};
