// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Interactable.h"
#include "MoonDoorControlPanel.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API AMoonDoorControlPanel : public AInteractable
{
	GENERATED_BODY()
	
public:

	AMoonDoorControlPanel();

	// The primary action for the door is to open if it is unlocked.
	virtual void ExecutePrimaryAction(APickup* pickup = NULL) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_leftDoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_rightDoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_ctrlPanelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_ctrlPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_LeftDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_RightDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoonDoor", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_objectCollider2;

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
