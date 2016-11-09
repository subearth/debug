// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CharacterControl/InteractableComponent.h"
#include "CharacterControl/HandComponent.h"
#include "CharacterControl/PocketComponent.h"
#include "CharacterControl/OxygenTankSlot.h"
#include "Objects/Pickup.h"
#include "Objects/Heart.h"
//#include <ForceFeedback.h>
//#include <ForceFeedbackEffect.h>
#include "SubEarthCharacter.generated.h"


UCLASS()
class SUBEARTH_API ASubEarthCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Control Modes
	enum ePlayerControlMode
	{
		PC,
		SWIM,
		PROPEL,
		VEHICLE,
		MENU
	};

	// Player control mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerControlMode)
	int m_PlayerControlMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerControlMode)
		bool m_IsInSuit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_SpeedPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_RotateSpeedPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_SpeedSwim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_RotateSpeedSwim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_SpeedPropel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_RotateSpeedPropel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_SpeedVehicle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeeds)
		float m_RotateSpeedVehicle;

	/****************************************/
	/*		START INVENTORY VARAIBLES		*/
	/****************************************/

	//TArray<FString> ShowInventory;


	/****************************************/
	/*		END INVENTORY VARAIBLES			*/
	/****************************************/

	/****************************************/
	/*			START HUD VARAIBLES			*/
	/****************************************/

	/*The player's initial oxygen level*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_initialOxygen;

	/*The player's current oxygen level*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_currentOxygen;

	/*The player's oxygen use rate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_oxygenUseRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		FString m_leftOxygenString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		FString m_rightOxygenString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_leftOxygenTank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_rightOxygenTank;

	/*The player's left tank's oxygen level*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_leftOxygenLevel;

	/*The player's left tank's oxygen percentage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_leftOxygenPercent;

	/*The player's right tank's oxygen level*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_rightOxygenLevel;

	/*The player's right tank's oxygen percentage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OxygenTank)
		float m_rightOxygenPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lungs)
		bool m_canSuffocate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lungs)
		float m_maxBreath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lungs)
		float m_currentBreath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lungs)
		float m_shakeAtPercentBreath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lungs)
		FLinearColor m_deathColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lungs)
		FLinearColor m_warningColor;

	/****************************************/
	/*			END HUD VARAIBLES			*/
	/****************************************/

	/****************************************/
	/*			START HUD METHODS			*/
	/****************************************/

	///*Accessor functon for Initial Oxygen */
	UFUNCTION(BlueprintPure, Category = "OxygenTank")
		float GetInitialOxygen();

	///*Accessor functon for Current Oxygen */
	UFUNCTION(BlueprintPure, Category = "OxygenTank")
		float GetCurrentOxygen();

	///*Updates the players current oxygen
	//*@param Oxygen This is the amount by which the player's Oxygen level will change  . It can be positive or negative.
	//*/
	UFUNCTION(BlueprintCallable, Category = "OxygenTank")
		float UpdateCurrentOxygen(float Oxygen);

	/****************************************/
	/*			END HUD METHODS			*/
	/****************************************/


	// Sets default values for this character's properties
	ASubEarthCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Returns PlayerCameraComponent subobject
	FORCEINLINE class UCameraComponent* GetPlayerCameraComponent() const { return PlayerCameraComponent; }

	// Left Hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = leftHand, meta = (AllowPrivateAccess = "true"))
		class UHandComponent* m_leftHand;

	// Right Hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = rightHand, meta = (AllowPrivateAccess = "true"))
		class UHandComponent* m_rightHand;

	UInteractableComponent* GetOverlappedComponent(UPrimitiveComponent* otherComponent);

	
	UFUNCTION(BlueprintCallable, Category = "ControlMode")
		int UseSwimMode(int holder);

	UFUNCTION(BlueprintCallable, Category = "ControlMode")
		int UsePropelMode(int holder);

	UFUNCTION(BlueprintCallable, Category = "ControlMode")
		int UseVehicleMode(int holder);

	UFUNCTION(BlueprintCallable, Category = "ControlMode")
		int UseMenuMode(int holder);

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LeftHandButton1();
	void LeftHandButton2();
	void LeftHandButton3();
	void LeftHandButton4();
	void RightHandButton1();
	void RightHandButton2();
	void RightHandButton3();
	void RightHandButton4();

	// Most pickups and interactables you can simple click and grab or use them. 
	// This function will grab or use an pickup or interactable respectively.
	void LeftHandToggleGrab(void);

	// On occassion a pickup or an interactable will require that you hold down the 
	// trigger and move your hand to interact with it. In these situations, the left
	// and right hand toggle grab will latch the hand to the object, and this function
	// will clear the latch.
	void LeftHandRelease(void);
	
	// Most pickups and interactables you can simple click and grab or use them. 
	// This function will grab or use an pickup or interactable respectively.
	void RightHandToggleGrab(void);

	// On occassion a pickup or an interactable will require that you hold down the 
	// trigger and move your hand to interact with it. In these situations, the left
	// and right hand toggle grab will latch the hand to the object, and this function
	// will clear the latch.
	void RightHandRelease(void);
	
	void RightHandTranslateUp(void);
	void RightHandTranslateDown(void);

	void MapMotionControllersToHands();

	// Bind functionality to input for PC controls
	void SetupControlsPC();

	// Bind functionality to input for Vehicle controls
	void SetupControlsVehicle();

	// Cycle through the control modes
	void CyclePlayerControlMode();

	// Move forward and backward
	void MoveForward(float val);

	// Stafe left and right
	void MoveRight(float val);

	// Left Swim
	void LeftSwim(float val);

	// Right Swim
	void RightSwim(float val);

	// Left Propel
	void LeftPropel(float val);

	// Right Propel
	void RightPropel(float val);
	
	/****************************************/
	/*		START INVENTORY METHODS			*/
	/****************************************/

	/* Handles pickup and inventory */
	void Inventory();

	/****************************************/
	/*		END INVENTORY METHODS			*/
	/****************************************/

private:

	// Player camera scene component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraControl, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* PlayerCameraSceneComponent;

	// Player camera:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* PlayerCameraComponent;

	// Left Motion controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMotionControllerComponent* L_MotionController;

	// Right Motion controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMotionControllerComponent* R_MotionController;

	// Player rig component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraControl, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* PlayerRigComponent;

	// HMD Location and rotation
	FVector m_PlayerHMDLocation;
	FRotator m_PlayerHMDRotation;
	
	FVector m_LeftLastLocation;
	FVector m_RightLastLocation;

	// The Sub earth character has four pockets to store picked up objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UPocketComponent* m_pocketLeftShoulder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UPocketComponent* m_pocketRightShoulder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UPocketComponent* m_pocketLeftLeg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UPocketComponent* m_pocketRightLeg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UOxygenTankSlot* m_oxygenTankSlotLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UOxygenTankSlot* m_oxygenTankSlotRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_heartCollider;
	UFUNCTION()
		void HeartTriggerEnter(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void HeartTriggerExit(UPrimitiveComponent* overlappedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex);
	
};
