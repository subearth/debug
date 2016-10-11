// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "SubEarthCharacter.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"


// Sets default values
ASubEarthCharacter::ASubEarthCharacter()
{
	// Initialize member variables:
	
	m_PlayerHMDLocation = FVector(0.0f, 0.0f, 0.0f);
	m_PlayerHMDRotation = FRotator(0.0f, 0.0f, 0.0f);

	m_SpeedPC = 1.0f;
	m_RotateSpeedPC = 1.0f;
	
	m_SpeedSwim = 1.0f;
	m_RotateSpeedSwim = 1.0f;

	m_SpeedPropel = 1.0f;
	m_RotateSpeedPropel = 1.0f;

	m_SpeedVehicle = 1.0f;
	m_RotateSpeedVehicle = 1.0f;

	m_initialOxygen = 60.f;
	m_currentOxygen = 60.f;
	m_oxygenUseRate = 1.f;
	m_leftOxygenPercent = 0.0;
	m_rightOxygenPercent = 0.0;
	m_leftOxygenString = FString::SanitizeFloat(0.f);
	m_rightOxygenString = FString::SanitizeFloat(0.f);

	// Initialize components:

	// Set size for collision capsule:
	GetCapsuleComponent()->InitCapsuleSize(10.0, 96.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = false;
	GetCapsuleComponent()->bHiddenInGame = true;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Player Camera Scene Component:
	PlayerCameraSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerCameraScene"));
	PlayerCameraSceneComponent->SetupAttachment(GetCapsuleComponent());
	PlayerCameraSceneComponent->RelativeLocation = FVector(0.0f, 0.0f, 60.0f); // Position the camera
	
	// Create the Player Camera:
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->RelativeLocation = FVector(0.0f, 0.0f, 0.0f); // Position the camera
	PlayerCameraComponent->RelativeRotation = FRotator(0.0f, 0.0f, 0.0f);
	PlayerCameraComponent->SetupAttachment(PlayerCameraSceneComponent);
	
	// Create Left Motion Controller:
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->Hand = EControllerHand::Left;
	L_MotionController->SetupAttachment(PlayerCameraSceneComponent);
	
	// Create Right Motion Controller:
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(PlayerCameraSceneComponent);

	// Initialize the left/right locations:
	m_LeftLastLocation = L_MotionController->GetComponentLocation();
	m_RightLastLocation = R_MotionController->GetComponentLocation();

	// Create left hand component
	m_leftHand = CreateDefaultSubobject<UHand>(TEXT("L_Hand"));
	
	// Create right hand component
	m_rightHand = CreateDefaultSubobject<UHand>(TEXT("R_Hand"));
	
	// Attach the left hand to the motion controller:
	USceneComponent* lhs = m_leftHand->GetHandSceneComponent();
	lhs->SetupAttachment(L_MotionController);
	lhs->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	//lhs->RelativeLocation = m_LeftLastLocation;

	// Attach the right hand to the motion controller:
	USceneComponent* rhs = m_rightHand->GetHandSceneComponent();
	rhs->SetupAttachment(R_MotionController);
	rhs->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	//rhs->RelativeLocation = m_RightLastLocation;

	// Add the hand mesh to the left and right mesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HandMesh(TEXT("StaticMesh'/Game/Assets/Character/Hand'"));
	if (HandMesh.Object)
	{
		m_leftHand->handMesh->SetStaticMesh(HandMesh.Object);
		m_leftHand->handMesh->SetRelativeLocation(FVector(0.f, -2.f, 0.f));
		m_leftHand->handMesh->SetRelativeRotation(FRotator(-45.f, 180.f, 0.f));
		m_leftHand->handMesh->SetRelativeScale3D(FVector(6.f, -6.f, 6.f));
		m_rightHand->handMesh->SetStaticMesh(HandMesh.Object);
		m_rightHand->handMesh->SetRelativeLocation(FVector(0.f, -2.f, 0.f));
		m_rightHand->handMesh->SetRelativeRotation(FRotator(-45.f, 180.f, 0.f));
		m_rightHand->handMesh->SetRelativeScale3D(FVector(6.f, 6.f, 6.f));

		m_leftHand->handCollider->bHiddenInGame = false;
		m_rightHand->handCollider->bHiddenInGame = false;
	}

	// Create the Rig Scene Component:
	PlayerRigComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRigScene"));
	PlayerRigComponent->SetupAttachment(GetCapsuleComponent());
	PlayerRigComponent->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);

	// Create four pockets
	m_pocketLeftShoulder = CreateDefaultSubobject<UPocketComponent>(TEXT("LEFT_SHOULD_POCKET"));
	m_pocketRightShoulder = CreateDefaultSubobject<UPocketComponent>(TEXT("RIGHT_SHOULD_POCKET"));
	m_pocketLeftLeg = CreateDefaultSubobject<UPocketComponent>(TEXT("LEFT_LEG_POCKET"));
	m_pocketRightLeg = CreateDefaultSubobject<UPocketComponent>(TEXT("RIGHT_LEG_POCKET"));

	// Attach the pockets to the RIG component
	m_pocketLeftShoulder->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	m_pocketRightShoulder->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	m_pocketLeftLeg->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	m_pocketRightLeg->GetObjectRoot()->SetupAttachment(PlayerRigComponent);

	// Setup the location of the pockets
	m_pocketLeftShoulder->SetRelativePosition(FVector(10.0f, -20.0f, 30.0f));
	m_pocketRightShoulder->SetRelativePosition(FVector(10.0f, +20.0f, 30.0f));
	m_pocketLeftLeg->SetRelativePosition(FVector(10.0f, -20.0f, 0.0f));
	m_pocketRightLeg->SetRelativePosition(FVector(10.0f, 20.0f, 0.0f));
	
	// Create two oxygen tank slots
	m_oxygenTankSlotLeft = CreateDefaultSubobject<UOxygenTankSlot>(TEXT("BACK_LEFT_OXYGEN_SLOT"));
	m_oxygenTankSlotRight = CreateDefaultSubobject<UOxygenTankSlot>(TEXT("BACK_RIGHT_OXYGEN_SLOT"));

	// Attach the oxygen tank slots to the RIG component
	m_oxygenTankSlotLeft->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	m_oxygenTankSlotRight->GetObjectRoot()->SetupAttachment(PlayerRigComponent);


	// TODO location was picked arbitrarly. Need to setup actual location

	// Setup the location of the oxygen tank slots
	m_oxygenTankSlotLeft->SetRelativePosition(FVector(-10.0f, -35.0f, 0.0f));
	m_oxygenTankSlotRight->SetRelativePosition(FVector(-10.0f, +35.0f, 0.0f));

	m_heartCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HEART"));
	m_heartCollider->SetupAttachment(PlayerRigComponent);
	m_heartCollider->SetRelativeLocation(FVector(10.0f, 0.0f, 30.0f));
	m_heartCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_heartCollider->bGenerateOverlapEvents = true;
	m_heartCollider->OnComponentBeginOverlap.AddDynamic(this, &ASubEarthCharacter::HeartTriggerEnter);
	m_heartCollider->OnComponentEndOverlap.AddDynamic(this, &ASubEarthCharacter::HeartTriggerExit);


	m_PlayerControlMode = (int)ePlayerControlMode::PC;
	SetupControlsPC();
}

/******************************************************************************/
// Called when the game starts or when spawned
void ASubEarthCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Reset the headset (to get hands to be relative to the HMD):
	//UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0.0f, EOrientPositionSelector::Position);
	
}
/******************************************************************************/
// Called every frame
void ASubEarthCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UpdateCurrentOxygen(DeltaTime * m_oxygenUseRate);
	
	GetCapsuleComponent()->UpdateChildTransforms();
	if (m_PlayerControlMode != (int)ePlayerControlMode::PC)
	{
		if (PlayerCameraComponent->GetComponentRotation().Pitch > -63.0f)
		{
			PlayerRigComponent->SetWorldRotation(FRotator(0.f, PlayerCameraComponent->GetComponentRotation().Yaw, 0.f));
		}
	}
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0.0f, EOrientPositionSelector::Position);
	
	//UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(m_PlayerHMDRotation, m_PlayerHMDLocation);
}

/******************************************************************************/
UInteractableComponent* ASubEarthCharacter::GetOverlappedComponent(UPrimitiveComponent* otherComponent)
{
	UInteractableComponent* ret = NULL;

	if (otherComponent == m_pocketLeftShoulder->m_objectCollider)
	{
		ret = m_pocketLeftShoulder;
	}
	else if (otherComponent == m_pocketRightShoulder->m_objectCollider)
	{
		ret = m_pocketRightShoulder;
	}
	else if (otherComponent == m_pocketLeftLeg->m_objectCollider)
	{
		ret = m_pocketLeftLeg;
	}
	else if (otherComponent == m_pocketRightLeg->m_objectCollider)
	{
		ret = m_pocketRightLeg;
	}
	else if (otherComponent == m_oxygenTankSlotLeft->m_objectCollider)
	{
		ret = m_oxygenTankSlotLeft;
	}
	else if (otherComponent == m_oxygenTankSlotRight->m_objectCollider)
	{
		ret = m_oxygenTankSlotRight;
	}

	return ret;
}

/******************************************************************************/
// Called to bind functionality to input
void ASubEarthCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("CycleMode", IE_Pressed, this, &ASubEarthCharacter::CyclePlayerControlMode);

	// Shoulder Button left and right controller
	PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &ASubEarthCharacter::Inventory);

	// L-Trigger, Q
	PlayerInputComponent->BindAction("LeftHandToggleGrab", IE_Pressed, this, &ASubEarthCharacter::LeftHandToggleGrab);

	// R-Trigger, E
	PlayerInputComponent->BindAction("RightHandToggleGrab", IE_Pressed, this, &ASubEarthCharacter::RightHandToggleGrab);

	// (L) face button 2, 3, 4,  Keyboard 1, 2, 3
	PlayerInputComponent->BindAction("LeftHandButton2", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton2);
	PlayerInputComponent->BindAction("LeftHandButton3", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton3);
	PlayerInputComponent->BindAction("LeftHandButton4", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton4);

	// (R) face button 2, 3, 4,  Keyboard 4, 5, 6
	PlayerInputComponent->BindAction("RightHandButton2", IE_Pressed, this, &ASubEarthCharacter::RightHandButton2);
	PlayerInputComponent->BindAction("RightHandButton3", IE_Pressed, this, &ASubEarthCharacter::RightHandButton3);
	PlayerInputComponent->BindAction("RightHandButton4", IE_Pressed, this, &ASubEarthCharacter::RightHandButton4);

	// Keyboard only: W, A, S, D, Mouse X, Mouse Y
	PlayerInputComponent->BindAxis("MoveForward", this, &ASubEarthCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubEarthCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// L/R Face button 1 (Swim and Propel are mutually exclusive)
	PlayerInputComponent->BindAxis("LeftSwim", this, &ASubEarthCharacter::LeftSwim);
	PlayerInputComponent->BindAxis("RightSwim", this, &ASubEarthCharacter::RightSwim);

	// L/R Face button 1 (Swim and Propel are mutually exclusive)
	PlayerInputComponent->BindAxis("LeftPropel", this, &ASubEarthCharacter::LeftPropel);
	PlayerInputComponent->BindAxis("RightPropel", this, &ASubEarthCharacter::RightPropel);
}
/******************************************************************************/

// Bind functionality to input for PC controls
void ASubEarthCharacter::SetupControlsPC()
{
	PlayerRigComponent->RelativeRotation = FRotator::ZeroRotator;
	// Allow for mouse yaw and pitch:
	bUseControllerRotationYaw = true;
	PlayerCameraComponent->bUsePawnControlRotation = true;
	
	// Position the left and right hands statically in front of the body
	L_MotionController->RelativeLocation = FVector::ZeroVector;
	USceneComponent* lhs = m_leftHand->GetHandSceneComponent();
	lhs->RelativeLocation = FVector(120.0f, -25.0f, -20.0f);

	R_MotionController->RelativeLocation = FVector::ZeroVector; 
	USceneComponent* rhs = m_rightHand->GetHandSceneComponent();
	rhs->RelativeLocation = FVector(120.0f, 25.0f, -20.0f);
}
/******************************************************************************/

// Bind functionality to input for Propel and Swim controls
void ASubEarthCharacter::MapMotionControllersToHands()
{
	// Allow for mouse yaw and pitch:
	bUseControllerRotationYaw = false;
	PlayerCameraComponent->bUsePawnControlRotation = false;
	//PlayerRigComponent->RelativeRotation = FRotator::ZeroRotator;

	// Reintialize the hand locations:
	m_LeftLastLocation = L_MotionController->GetComponentLocation();
	m_RightLastLocation = R_MotionController->GetComponentLocation();

	// Position the left and right hands over the motion controllers
	USceneComponent* lhs = m_leftHand->GetHandSceneComponent();
	//lhs->RelativeLocation = m_LeftLastLocation;
	lhs->RelativeLocation = FVector(0.f, 0.f, 0.f);

	USceneComponent* rhs = m_rightHand->GetHandSceneComponent();
	//rhs->RelativeLocation = m_RightLastLocation;
	rhs->RelativeLocation = FVector(0.f, 0.f, 0.f);
}
/******************************************************************************/

// Bind functionality to input for Vehicle controls
void ASubEarthCharacter::SetupControlsVehicle()
{
	// Empty
}

/******************************************************************************/
// For development: cycles the player controls
void ASubEarthCharacter::CyclePlayerControlMode()
{
	switch ((ePlayerControlMode)m_PlayerControlMode)
	{
		case ePlayerControlMode::PC:
		{
			m_PlayerControlMode = ePlayerControlMode::SWIM;
			MapMotionControllersToHands();
			UE_LOG(LogTemp, Log, TEXT("Player Control Mode: SWIM"));
			break;
		}
		case ePlayerControlMode::SWIM:
		{
			m_PlayerControlMode = ePlayerControlMode::PROPEL;
			MapMotionControllersToHands();
			UE_LOG(LogTemp, Log, TEXT("Player Control Mode: PROPEL"));
			break;
		}
		case ePlayerControlMode::PROPEL:
		{
			// Vehicle not fully setup yet.
			m_PlayerControlMode = ePlayerControlMode::VEHICLE;
			SetupControlsVehicle();
			UE_LOG(LogTemp, Log, TEXT("Player Control Mode: VEHICLE"));
			break;
		}
		case ePlayerControlMode::VEHICLE:
		{
			m_PlayerControlMode = ePlayerControlMode::PC;
			SetupControlsPC();
			UE_LOG(LogTemp, Log, TEXT("Player Control Mode: PC"));
			break;
		}
		default:
		{
			UE_LOG(LogTemp, Log, TEXT("Should not get here. Attempted Mode: %d"), m_PlayerControlMode);
			break;
		}
	}	
}

/******************************************************************************/
// Movement in the direction of the camera
void ASubEarthCharacter::MoveForward(float val)
{
	if (val != 0.0f)
	{		
		FVector cameraForward = PlayerCameraComponent->GetForwardVector();
		float disp = val * m_SpeedPC;
		AddMovementInput(cameraForward, disp);
	}
}

/******************************************************************************/
// Movement lateral to the direction of the camera
void ASubEarthCharacter::MoveRight(float val)
{
	if (val != 0.0f)
	{
		FVector cameraRight = PlayerCameraComponent->GetRightVector();	
		float disp = val * m_SpeedPC;
		AddMovementInput(cameraRight, disp);
	}
}

/******************************************************************************/
// Left Swim
void ASubEarthCharacter::LeftSwim(float val)
{
	if (m_PlayerControlMode == (int)ePlayerControlMode::SWIM)
	{
		FVector handLocation = L_MotionController->GetComponentLocation();
		FVector handDifference = m_LeftLastLocation - handLocation;
		float movementSize = handDifference.Size();
		handDifference.Normalize();
		FVector handUp = L_MotionController->GetUpVector();

		float alignment = FVector::DotProduct(handUp, handDifference);
		
		if (alignment > 0.5)
		{
			AddMovementInput(handDifference, m_SpeedSwim*movementSize);
		}
		//AddMovementInput(handUp, dist);
		
		// Rotate towards the swim direction:
		//FRotator handRotation = L_MotionController->GetComponentRotation();
		//FRotator playerRotation = GetCapsuleComponent()->GetComponentRotation();
		//float angle = (handRotation.Yaw - playerRotation.Yaw) * m_RotateSpeedPropel * val;
		////GetCapsuleComponent()->AddWorldRotation(FRotator(0.0f, angle, 0.0f));
		//AddControllerYawInput(angle);

		// Update the last location:
		m_LeftLastLocation = handLocation;
	}
	
}

/******************************************************************************/
// Right Swim
void ASubEarthCharacter::RightSwim(float val)
{
	if (m_PlayerControlMode == (int)ePlayerControlMode::SWIM)
	{
		FVector handLocation = R_MotionController->GetComponentLocation();
		FVector handDifference = m_RightLastLocation - handLocation;
		float movementSize = handDifference.Size();
		handDifference.Normalize();
		FVector handUp = R_MotionController->GetUpVector();

		float alignment = FVector::DotProduct(handUp, handDifference);
		
		if (alignment > 0.5)
		{
			AddMovementInput(handDifference, m_SpeedSwim*movementSize);
		}

		// Rotate towards the swim direction:
		//FRotator handRotation = L_MotionController->GetComponentRotation();
		//FRotator playerRotation = GetCapsuleComponent()->GetComponentRotation();
		//float angle = (handRotation.Yaw - playerRotation.Yaw) * m_RotateSpeedPropel * val;
		////GetCapsuleComponent()->AddWorldRotation(FRotator(0.0f, angle, 0.0f));
		//AddControllerYawInput(angle);

		// Update the last location:
		m_RightLastLocation = handLocation;

		
		
	}
}

/******************************************************************************/
// Left Propel
void ASubEarthCharacter::LeftPropel(float val)
{
	//if ((m_PlayerControlMode == (int)ePlayerControlMode::PROPEL) && (val != 0.0f))
	if ((m_PlayerControlMode == (int)ePlayerControlMode::PROPEL))
	{
		// Move in the direction of the thruster:
		FVector handForward = L_MotionController->GetForwardVector();
		float disp = val * m_SpeedPropel;
		AddMovementInput(handForward, disp);
		
		// Rotate towards the thruster:
		FRotator handRotation = L_MotionController->RelativeRotation; // GetComponentRotation();
		UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(m_PlayerHMDRotation, m_PlayerHMDLocation);
		float mag = handRotation.Yaw - m_PlayerHMDRotation.Yaw;
		float angle = FMath::Sign(mag) * m_RotateSpeedPropel * val;
		if (mag > -90.0f && mag < 90.0f)
		{
			//AddControllerYawInput(FMath::DegreesToRadians(angle));
		}
		
	}
}

/******************************************************************************/
// Right Propel
void ASubEarthCharacter::RightPropel(float val)
{
	//if ((m_PlayerControlMode == (int)ePlayerControlMode::PROPEL) && (val != 0.0f))
	if ((m_PlayerControlMode == (int)ePlayerControlMode::PROPEL))
	{
		// Move in the direction of the thruster:
		FVector handForward = R_MotionController->GetForwardVector();
		float disp = val * m_SpeedPropel;
		AddMovementInput(handForward, disp);

		// Rotate towards the thruster:
		FRotator handRotation = R_MotionController->RelativeRotation; // GetComponentRotation();
		UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(m_PlayerHMDRotation, m_PlayerHMDLocation);
		float mag = handRotation.Yaw - m_PlayerHMDRotation.Yaw;
		float angle = FMath::Sign(mag) * m_RotateSpeedPropel * val;
		if (mag > -90.0f && mag < 90.0f)
		{
			//AddControllerYawInput(FMath::DegreesToRadians(angle));
		}
	}
}

/******************************************************************************/
// Get the air capacity of the player:
float ASubEarthCharacter::GetInitialOxygen()
{
	return m_initialOxygen;
}

/******************************************************************************/
// Get how much Oxygen the player still has:
float ASubEarthCharacter::GetCurrentOxygen()
{
	return m_currentOxygen;
}

/******************************************************************************/
// Add or remove oxygen from the player
float ASubEarthCharacter::UpdateCurrentOxygen(float oxygen)
{
	float oxygenToSpendLeft = oxygen / 2.f;
	float oxygenToSpendRight = oxygen / 2.f;
	// Get our tank levels:
	float leftInitial = m_oxygenTankSlotLeft->GetTankInitialLevel();
	float rightInitial = m_oxygenTankSlotRight->GetTankInitialLevel();
	float leftLevel = m_oxygenTankSlotLeft->GetTankCurrentLevel();
	float rightLevel = m_oxygenTankSlotRight->GetTankCurrentLevel();
	
	// Use what we can on the left:
	if (leftLevel > oxygenToSpendLeft)
	{
		leftLevel -= oxygenToSpendLeft;
		oxygenToSpendLeft = 0.f;
	}
	else
	{
		oxygenToSpendLeft -= leftLevel;
		leftLevel = 0.f;
	}

	// Use what we can on the right:
	if (rightLevel > oxygenToSpendRight)
	{
		rightLevel -= oxygenToSpendRight;
		oxygenToSpendRight = 0.f;
	}
	else
	{
		oxygenToSpendRight -= rightLevel;
		rightLevel = 0.f;
	}

	// Check what we have left to spend:
	float remaining = oxygenToSpendLeft + oxygenToSpendRight;
	
	// Try to use it on the left:
	if (remaining > 0.f)
	{
		if (leftLevel > remaining)
		{
			leftLevel -= remaining;
			remaining = 0.f;
		}
		else
		{
			remaining -= leftLevel;
			leftLevel = 0.f;
		}
	}

	// Try to use it on the right:
	if (remaining > 0.f)
	{
		if (rightLevel > remaining)
		{
			rightLevel -= remaining;
			remaining = 0.f;
		}
		else
		{
			remaining -= rightLevel;
			rightLevel = 0.f;
		}
	}

	// Begin suffocation if we still have some to spend:
	if (remaining > 0.f)
	{
		// Slowly die!
	}

	// Update our tanks on where they are:
	m_oxygenTankSlotLeft->SetTankCurrentLevel(leftLevel);
	m_oxygenTankSlotRight->SetTankCurrentLevel(rightLevel);

	// Update the HUD data:
	m_leftOxygenPercent = 0.31f + 0.19f * (leftLevel / leftInitial);
	m_rightOxygenPercent = 0.31f + 0.19f * (rightLevel / rightInitial);

	m_leftOxygenString = FString::FromInt((int)leftLevel);
	m_rightOxygenString = FString::FromInt((int)rightLevel);	

	return 0;
}

/******************************************************************************/
void ASubEarthCharacter::LeftHandButton1()
{
	m_leftHand->PressButton1();
}
void ASubEarthCharacter::LeftHandButton2()
{
	m_leftHand->PressButton2();
}
void ASubEarthCharacter::LeftHandButton3()
{
	m_leftHand->PressButton3();
}
void ASubEarthCharacter::LeftHandButton4()
{
	m_leftHand->PressButton4();
}
/******************************************************************************/
void ASubEarthCharacter::RightHandButton1()
{
	m_rightHand->PressButton1();
}
void ASubEarthCharacter::RightHandButton2()
{
	m_rightHand->PressButton2();
}
void ASubEarthCharacter::RightHandButton3()
{
	m_rightHand->PressButton3();
}
void ASubEarthCharacter::RightHandButton4()
{
	m_rightHand->PressButton4();
}

/******************************************************************************/
void ASubEarthCharacter::LeftHandToggleGrab()
{
	m_leftHand->UseHand();
}

/******************************************************************************/
void ASubEarthCharacter::RightHandToggleGrab()
{
	m_rightHand->UseHand();
}

/****************************************************************************************************************************************************/
void ASubEarthCharacter::Inventory()
{
	FString p1 = m_pocketLeftShoulder->GetNameOfPickupInPocket();
	FString p2 = m_pocketRightShoulder->GetNameOfPickupInPocket();
	FString p3 = m_pocketLeftLeg->GetNameOfPickupInPocket();
	FString p4 = m_pocketRightLeg->GetNameOfPickupInPocket();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Item: %s "), *p1));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Item: %s "), *p2));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Item: %s "), *p3));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Item: %s "), *p4));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("End of Inventory"));
}
/******************************************************************************/
void ASubEarthCharacter::HeartTriggerEnter(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) {

	if (otherActor->IsA(AHeart::StaticClass())) {
		m_PlayerControlMode = ePlayerControlMode::PROPEL;
		MapMotionControllersToHands();
		UE_LOG(LogTemp, Log, TEXT("Player Control Mode: PROPEL"));
		//Destroy(otherActor);
	}
}

void ASubEarthCharacter::HeartTriggerExit(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex) {

}