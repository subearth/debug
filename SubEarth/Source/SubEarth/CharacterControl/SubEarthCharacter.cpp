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

	m_PlayerControlMode = (int)ePlayerControlMode::PROPEL;
	m_swimEnabled = false;
	m_propelEnabled = true;

	m_SpeedPC = 1.0f;
	m_RotateSpeedPC = 1.0f;
	
	m_SpeedSwim = 1.0f;
	m_RotateSpeedSwim = 1.0f;

	m_SpeedPropel = 1.0f;
	m_RotateSpeedPropel = 1.0f;

	m_SpeedVehicle = 1.0f;
	m_RotateSpeedVehicle = 1.0f;

	m_initialOxygen = 400.0f;
	m_currentOxygen = m_initialOxygen;
	m_oxygenUseRate = 0.05f;

	// Initialize components:

	// Set size for collision capsule:
	GetCapsuleComponent()->InitCapsuleSize(22.0, 96.0f);

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

	// Initialize the hand locations:
	m_LeftLastLocation = L_MotionController->GetComponentLocation();
	m_RightLastLocation = R_MotionController->GetComponentLocation();

	// Create left hand component and position over the motion controllers
	m_leftHand = CreateDefaultSubobject<UHand>(TEXT("LeftHand"));
	m_leftHand->SetMotionController(L_MotionController);
	USceneComponent* lhs = m_leftHand->GetHandSceneComponent();
	lhs->SetupAttachment(L_MotionController);
	lhs->RelativeLocation = m_LeftLastLocation;

	// Create right hand component and position over the motion controllers
	m_rightHand = CreateDefaultSubobject<UHand>(TEXT("RightHand"));
	m_rightHand->SetMotionController(R_MotionController);
	USceneComponent* rhs = m_rightHand->GetHandSceneComponent();
	rhs->SetupAttachment(R_MotionController);
	rhs->RelativeLocation = m_RightLastLocation;

	MapMotionControllersToHands();
	//SetupControlsPC();
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

	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0.0f, EOrientPositionSelector::Position);
	//UHeadMountedDisplayFunctionLibrary::position
	// Update the player Oxygen levels:
	UpdateCurrentOxygen(-DeltaTime * m_oxygenUseRate * m_initialOxygen);
	//UE_LOG(LogTemp, Log, TEXT("Oxygen: %f"), m_currentOxygen);
	
	// Place the player at the HMD:
	if (m_PlayerControlMode == (int)ePlayerControlMode::PC)
	{
		
	}
	else
	{
		//UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(m_PlayerHMDRotation, m_PlayerHMDLocation);
		//PlayerCameraComponent->SetWorldRotation(m_PlayerHMDRotation);
		//UE_LOG(LogTemp, Log, TEXT("HMD Rotation: %f, %f, %f"), m_PlayerHMDRotation.Yaw, m_PlayerHMDRotation.Pitch, m_PlayerHMDRotation.Roll);
	}

}
/******************************************************************************/
// Called to bind functionality to input
void ASubEarthCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("CycleMode", IE_Pressed, this, &ASubEarthCharacter::CyclePlayerControlMode);

	// Player controls:
	PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &ASubEarthCharacter::Inventory);

	// L-Trigger, Q
	PlayerInputComponent->BindAction("LeftHandToggleGrab", IE_Pressed, this, &ASubEarthCharacter::LeftHandToggleGrab);
	PlayerInputComponent->BindAction("LeftHandToggleGrab", IE_Released, this, &ASubEarthCharacter::LeftHandToggleGrab);

	// R-Trigger, E
	PlayerInputComponent->BindAction("RightHandToggleGrab", IE_Pressed, this, &ASubEarthCharacter::RightHandToggleGrab);
	PlayerInputComponent->BindAction("RightHandToggleGrab", IE_Released, this, &ASubEarthCharacter::RightHandToggleGrab);

	// (L) face button 2, 3, 4,  Keyboard 1, 2, 3
	PlayerInputComponent->BindAction("LeftHandButton2", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton2);
	PlayerInputComponent->BindAction("LeftHandButton3", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton3);
	PlayerInputComponent->BindAction("LeftHandButton4", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton4);

	// (R) face button 2, 3, 4,  Keyboard 4, 5, 6
	PlayerInputComponent->BindAction("RightHandButton2", IE_Pressed, this, &ASubEarthCharacter::RightHandButton2);
	PlayerInputComponent->BindAction("RightHandButton3", IE_Pressed, this, &ASubEarthCharacter::RightHandButton3);
	PlayerInputComponent->BindAction("RightHandButton4", IE_Pressed, this, &ASubEarthCharacter::RightHandButton4);

	// Keyboard only: W A S D
	PlayerInputComponent->BindAxis("MoveForward", this, &ASubEarthCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubEarthCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

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
	// Position the left and right hands statically in front of the body
	USceneComponent* lhs = m_leftHand->GetHandSceneComponent();
	lhs->RelativeLocation = FVector(120.0f, -25.0f, -5.0f);

	USceneComponent* rhs = m_rightHand->GetHandSceneComponent();
	rhs->RelativeLocation = FVector(120.0f, 25.0f, -5.0f);
	UE_LOG(LogTemp, Log, TEXT("SetupControlsPC"));
}
/******************************************************************************/

// Bind functionality to input for Propel and Swim controls
void ASubEarthCharacter::MapMotionControllersToHands()
{
	// Reintialize the hand locations:
	m_LeftLastLocation = L_MotionController->GetComponentLocation();
	m_RightLastLocation = R_MotionController->GetComponentLocation();

	// Position the left and right hands over the motion controllers
	USceneComponent* lhs = m_leftHand->GetHandSceneComponent();
	lhs->RelativeLocation = m_LeftLastLocation;

	USceneComponent* rhs = m_rightHand->GetHandSceneComponent();
	rhs->RelativeLocation = m_RightLastLocation;
	UE_LOG(LogTemp, Log, TEXT("MapMotionControllersToHands"));

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
			m_propelEnabled = false;
			m_pcEnabled = false;
			m_swimEnabled = true;
			MapMotionControllersToHands();
			break;
		}
		case ePlayerControlMode::SWIM:
		{
			m_PlayerControlMode = ePlayerControlMode::PROPEL;
			m_propelEnabled = true;
			m_pcEnabled = false;
			m_swimEnabled = false;
			MapMotionControllersToHands();
			break;
		}
		case ePlayerControlMode::PROPEL:
		{
			// Vehicle not fully setup yet.
			m_PlayerControlMode = ePlayerControlMode::VEHICLE;
			m_propelEnabled = false;
			m_pcEnabled = false;
			m_swimEnabled = false;
			SetupControlsVehicle();
			break;
		}
		case ePlayerControlMode::VEHICLE:
		{
			m_PlayerControlMode = ePlayerControlMode::PC;
			m_propelEnabled = false;
			m_pcEnabled = true;
			m_swimEnabled = false;
			SetupControlsPC();
			break;
		}
		default:
		{
			UE_LOG(LogTemp, Log, TEXT("Should not get here. Mode Change: %d"), m_PlayerControlMode);
			break;
		}
	}	
	
	UE_LOG(LogTemp, Log, TEXT("Mode Change: %d"), m_PlayerControlMode);
}

/******************************************************************************/
// Movement in the direction of the camera
void ASubEarthCharacter::MoveForward(float val)
{
	if (m_pcEnabled && val != 0.0f)
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
	if (m_pcEnabled && val != 0.0f)
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
	FVector handLocation = L_MotionController->GetComponentLocation();
	FVector handDifference = m_LeftLastLocation - handLocation;
	FVector handUp = L_MotionController->GetUpVector();

	float dist = FVector::DotProduct(handUp, handDifference) * m_SpeedSwim;
	AddMovementInput(handUp, dist);

	// Rotate towards the swim direction:
	//FRotator handRotation = L_MotionController->GetComponentRotation();
	//FRotator playerRotation = GetCapsuleComponent()->GetComponentRotation();
	//float angle = (handRotation.Yaw - playerRotation.Yaw) * m_RotateSpeedPropel * val;
	////GetCapsuleComponent()->AddWorldRotation(FRotator(0.0f, angle, 0.0f));
	//AddControllerYawInput(angle);

	// Update the last location:
	m_LeftLastLocation = handLocation;
}

/******************************************************************************/
// Right Swim
void ASubEarthCharacter::RightSwim(float val)
{
	if (m_swimEnabled)
	{
		FVector handLocation = R_MotionController->GetComponentLocation();
		FVector handDifference = m_RightLastLocation - handLocation;
		FVector handUp = R_MotionController->GetUpVector();

		float dist = FVector::DotProduct(handUp, handDifference) * m_SpeedSwim;
		AddMovementInput(handUp, dist);

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
// Left Propel
void ASubEarthCharacter::LeftPropel(float val)
{
	if (m_propelEnabled && val != 0.0f)
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
	if (val != 0.0f)
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
void ASubEarthCharacter::UpdateCurrentOxygen(float oxygen)
{
	if (m_currentOxygen > 0)
	{
		m_currentOxygen = m_currentOxygen + oxygen;
	}
	else
		m_currentOxygen = 0;

}

/******************************************************************************/
void ASubEarthCharacter::LeftHandButton1()
{
	m_leftHand->PressButton1();
}
void ASubEarthCharacter::LeftHandButton2()
{

}
void ASubEarthCharacter::LeftHandButton3()
{

}
void ASubEarthCharacter::LeftHandButton4()
{

}
/******************************************************************************/
void ASubEarthCharacter::RightHandButton1()
{

}
void ASubEarthCharacter::RightHandButton2()
{

}
void ASubEarthCharacter::RightHandButton3()
{

}
void ASubEarthCharacter::RightHandButton4()
{

}

/******************************************************************************/
void ASubEarthCharacter::LeftHandToggleGrab()
{
	if (m_leftHand->IsGrabbing())
	{
		m_leftHand->SetGrabbing(false);
	}
	else
	{
		m_leftHand->SetGrabbing(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Left Hand isEmpty: %d"), m_leftHand->IsHandEmpty());
}

/******************************************************************************/
void ASubEarthCharacter::RightHandToggleGrab()
{
	if (m_rightHand->IsGrabbing())
	{
		m_rightHand->SetGrabbing(false);
	}
	else
	{
		m_rightHand->SetGrabbing(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Right Hand isEmpty: %d"), m_rightHand->IsHandEmpty());
}

/****************************************************************************************************************************************************/
void ASubEarthCharacter::Inventory()
{
	for (auto& eachItem : ShowInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Item: %s "), *eachItem));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("End of Inventory"));
}
