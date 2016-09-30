// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CharacterControl/Hand.h"
#include "Objects/Pickup.h"

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
		VEHICLE
	};

	enum Hand_e
	{
		NO_HAND_SELECTED,
		LEFT_HAND,
		RIGHT_HAND,
		BOTH_HANDS
	};

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

	TArray<FString> ShowInventory;


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
		void UpdateCurrentOxygen(float Oxygen);

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
		class UHand* m_leftHand;

	// Right Hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = rightHand, meta = (AllowPrivateAccess = "true"))
		class UHand* m_rightHand;

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

	void LeftHandToggleGrab(void);
	void RightHandToggleGrab(void);

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

	// Player control mode
	int m_PlayerControlMode;

	// HMD Location and rotation
	FVector m_PlayerHMDLocation;
	FRotator m_PlayerHMDRotation;
	
	FVector m_LeftLastLocation;
	FVector m_RightLastLocation;

	// The Sub earth character has four pockets to store picked up objects
	APickup* pocketLeftShoulder;
	APickup* pocketRightShoulder;
	APickup* pocketLeftLeg;
	APickup* pocketRightLeg;

	bool m_swimEnabled;
	bool m_propelEnabled;
	bool m_pcEnabled;
};
