// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Interactable.h"
#include "Matinee/MatineeActor.h"
#include "ToolBox.generated.h"

/**
*
*/
UCLASS()
class SUBEARTH_API AToolBox : public AInteractable
{
	GENERATED_BODY()

public:

	AToolBox();


	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableComponent", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_hingeSceneNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBoxComponent", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_handAreaCollider;

private:

	enum AnimStates_e
	{
		NOT_ANIMATING,
		OPENING,
		CLOSING
	};

	AnimStates_e m_animState;

	virtual void ExecuteAnimation(float delta_time) override;
	
	bool m_isClosed;
};
