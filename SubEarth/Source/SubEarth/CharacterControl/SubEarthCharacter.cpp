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
	
	m_PlayerControlMode = ePlayerControlMode::PROPEL;
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

	InitialOxygen = 100.0f;
	CurrentOxygen = InitialOxygen;
	OxygenUseRate = 0.01f;

	/*isLeftHandEmpty = true;
	isRightHandEmpty = true;*/

	// Initialize components:

	// Set size for collision capsule:
	GetCapsuleComponent()->InitCapsuleSize(22.0, 96.0f);
	//GetCapsuleComponent()->InitCapsuleSize(22.0, 30.0f);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the Player Camera Scene Component:
	PlayerCameraSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerCameraScene"));
	PlayerCameraSceneComponent->SetupAttachment(GetCapsuleComponent());
	PlayerCameraSceneComponent->RelativeLocation = FVector(0.0f, 0.0f, 60.0f); // Position the camera
	//PlayerCameraSceneComponent->RelativeLocation = FVector(0.0f, 0.0f, 0.0f); // Position the camera

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

	// Create left hand component
	leftHand = CreateDefaultSubobject<UHand>(TEXT("LeftHand"));

	// Create right hand component
	rightHand = CreateDefaultSubobject<UHand>(TEXT("RightHand"));
	
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
	UpdateCurrentOxygen(-DeltaTime * OxygenUseRate * InitialOxygen);
	UE_LOG(LogTemp, Log, TEXT("Oxegen: %f"), CurrentOxygen);
	
	// Place the player at the HMD:
	if (m_PlayerControlMode == ePlayerControlMode::PC)
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
void ASubEarthCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);
	
	check(InputComponent);
	PlayerInputComponent = InputComponent;

	ClearAllBindings();
	//SetupControlsPC();
	SetupControlsPropel();
}
/******************************************************************************/

// Clear all action and axis bindings:
void ASubEarthCharacter::ClearAllBindings()
{
	PlayerInputComponent->AxisBindings.Reset();
	PlayerInputComponent->ClearActionBindings();

	// Add the cycle mode (Ctrl + m): 
	PlayerInputComponent->BindAction("CycleMode", IE_Pressed, this, &ASubEarthCharacter::CyclePlayerControlMode);
}
/******************************************************************************/

// Bind functionality to input for PC controls
void ASubEarthCharacter::SetupControlsPC()
{
	//// Put hands in front:
	//USceneComponent* lhs = leftHand->GetHandSceneComponent();
	//lhs->SetupAttachment(RootComponent);
	//lhs->RelativeLocation = FVector(120.0f, -25.0f, -5.0f);

	//USceneComponent* rhs = rightHand->GetHandSceneComponent();
	//rhs->SetupAttachment(RootComponent);
	//rhs->RelativeLocation = FVector(120.0f, 25.0f, -5.0f);

	// Player controls:
	PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &ASubEarthCharacter::Inventory);
	PlayerInputComponent->BindAction("LeftPickItUp", IE_Pressed, this, &ASubEarthCharacter::LeftGrab);
	PlayerInputComponent->BindAction("LeftPickItUp", IE_Released, this, &ASubEarthCharacter::LeftDrop);
	PlayerInputComponent->BindAction("RightPickItUp", IE_Pressed, this, &ASubEarthCharacter::RightGrab);
	PlayerInputComponent->BindAction("RightPickItUp", IE_Released, this, &ASubEarthCharacter::RightDrop);

	// WASD bindings:
	PlayerInputComponent->BindAxis("MoveForward", this, &ASubEarthCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubEarthCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
}
/******************************************************************************/

// Bind functionality to input for Swim controls
void ASubEarthCharacter::SetupControlsSwim()
{
	/*USceneComponent* lhs = leftHand->GetHandSceneComponent();
	lhs->SetupAttachment(L_MotionController);
	lhs->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);

	USceneComponent* rhs = rightHand->GetHandSceneComponent();
	rhs->SetupAttachment(R_MotionController);
	rhs->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);*/

	// Reintialize the hand locations:
	m_LeftLastLocation = L_MotionController->GetComponentLocation();
	m_RightLastLocation = R_MotionController->GetComponentLocation();
	
	PlayerInputComponent->BindAxis("LeftSwim", this, &ASubEarthCharacter::LeftSwim);
	PlayerInputComponent->BindAxis("RightSwim", this, &ASubEarthCharacter::RightSwim);
}
/******************************************************************************/

// Bind functionality to input for Propel controls
void ASubEarthCharacter::SetupControlsPropel() 
{
	/*USceneComponent* lhs = leftHand->GetHandSceneComponent();
	lhs->SetupAttachment(L_MotionController);
	lhs->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);

	USceneComponent* rhs = rightHand->GetHandSceneComponent();
	rhs->SetupAttachment(R_MotionController);
	rhs->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);*/

	// Player controls:
	PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &ASubEarthCharacter::Inventory);
	PlayerInputComponent->BindAction("LeftPickItUp", IE_Pressed, this, &ASubEarthCharacter::LeftGrab);
	PlayerInputComponent->BindAction("LeftPickItUp", IE_Released, this, &ASubEarthCharacter::LeftDrop);
	PlayerInputComponent->BindAction("RightPickItUp", IE_Pressed, this, &ASubEarthCharacter::RightGrab);
	PlayerInputComponent->BindAction("RightPickItUp", IE_Released, this, &ASubEarthCharacter::RightDrop);

	PlayerInputComponent->BindAxis("LeftPropel", this, &ASubEarthCharacter::LeftPropel);
	PlayerInputComponent->BindAxis("RightPropel", this, &ASubEarthCharacter::RightPropel);

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
	ClearAllBindings();

	switch (m_PlayerControlMode)
	{
	case ePlayerControlMode::PC:
		m_PlayerControlMode = ePlayerControlMode::SWIM;
		SetupControlsSwim();
		break;
	case ePlayerControlMode::SWIM:
		m_PlayerControlMode = ePlayerControlMode::PROPEL;
		SetupControlsPropel();
		break;
	case ePlayerControlMode::PROPEL:
		m_PlayerControlMode = ePlayerControlMode::VEHICLE;
		SetupControlsVehicle();
		break;
	case ePlayerControlMode::VEHICLE:
		m_PlayerControlMode = ePlayerControlMode::PC;
		SetupControlsPC();
		break;
	default:
		m_PlayerControlMode = ePlayerControlMode::PC;
		SetupControlsPC();
		break;
	}	
	
	UE_LOG(LogTemp, Log, TEXT("Mode Change"));
	
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

/******************************************************************************/
// Left Propel
void ASubEarthCharacter::LeftPropel(float val)
{
	if (val != 0.0f)
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
	return InitialOxygen;
}

/******************************************************************************/
// Get how much Oxygen the player still has:
float ASubEarthCharacter::GetCurrentOxygen()
{
	return CurrentOxygen;
}

/******************************************************************************/
// Add or remove oxygen from the player
void ASubEarthCharacter::UpdateCurrentOxygen(float Oxygen)
{
	CurrentOxygen = CurrentOxygen + Oxygen;
}

/***************************************************************************************************************************************************/
void ASubEarthCharacter::LeftGrab()
{
	bIsLeftPickingUp = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Left hand Pickup"));

}

/***************************************************************************************************************************************************/
void ASubEarthCharacter::LeftDrop()
{
	bIsLeftPickingUp = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left Pickup complete"));

}

void ASubEarthCharacter::RightGrab()
{
	bIsRightPickingUp = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Right hand Pickup"));

}

/***************************************************************************************************************************************************/
void ASubEarthCharacter::RightDrop()
{
	bIsRightPickingUp = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Right Pickup complete"));

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