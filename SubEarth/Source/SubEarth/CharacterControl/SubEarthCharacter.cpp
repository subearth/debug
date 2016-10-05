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

	m_initialOxygen = 400.0f;
	m_currentOxygen = m_initialOxygen;
	m_oxygenUseRate = 0.05f;
	m_oxygenPercent = 1.0f;
	m_oxygenWarning = 0.0f;

	m_initialOxygenString = FString::SanitizeFloat(m_initialOxygen);
	m_currentOxygenString = FString::SanitizeFloat(m_currentOxygen);

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

	/* TODO 
	Ran out of time. I was trying to add the pockets to the actor. The pockets are
	interactable objects. Essentially, anything the hands can interact with are interactable
	objects. Take a look "UHand::UseHand()" for how I intended to use it. */

	// Create four pockets
	pocketLeftShoulder = CreateDefaultSubobject<UPocket>(TEXT("LEFT_SHOULD_POCKET"));
	pocketRightShoulder = CreateDefaultSubobject<UPocket>(TEXT("RIGHT_SHOULD_POCKET"));
	pocketLeftLeg = CreateDefaultSubobject<UPocket>(TEXT("LEFT_LEG_POCKET"));
	pocketRightLeg = CreateDefaultSubobject<UPocket>(TEXT("RIGHT_LEG_POCKET"));

	// Attach the pockets to the RIG component
	pocketLeftShoulder->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	pocketRightShoulder->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	pocketLeftLeg->GetObjectRoot()->SetupAttachment(PlayerRigComponent);
	pocketRightLeg->GetObjectRoot()->SetupAttachment(PlayerRigComponent);

	// Setup the location of the pockets
	pocketLeftShoulder->SetRelativePosition(FVector(-5.0f, -10.0f, 40.0f));
	pocketRightShoulder->SetRelativePosition(FVector(-5.0f, +10.0f, 40.0f));
	pocketLeftLeg->SetRelativePosition(FVector(-15.0f, -15.0f, -30.0f));
	pocketRightLeg->SetRelativePosition(FVector(-15.0f, 15.0f, -30.0f));

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

	// Update the player Oxygen levels:
	UpdateCurrentOxygen(-DeltaTime * m_oxygenUseRate * m_initialOxygen);
	
	//UE_LOG(LogTemp, Log, TEXT("Oxygen: %f"), m_currentOxygen);
	
	GetCapsuleComponent()->UpdateChildTransforms();
	if (m_PlayerControlMode != (int)ePlayerControlMode::PC)
	{
		PlayerRigComponent->SetWorldRotation(FRotator(0.f, PlayerCameraComponent->GetComponentRotation().Yaw, 0.f));
	}
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0.0f, EOrientPositionSelector::Position);
	
	//UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(m_PlayerHMDRotation, m_PlayerHMDLocation);

	

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
	
}

/******************************************************************************/
// Right Swim
void ASubEarthCharacter::RightSwim(float val)
{
	if (m_PlayerControlMode == (int)ePlayerControlMode::SWIM)
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
void ASubEarthCharacter::UpdateCurrentOxygen(float oxygen)
{
	if (m_currentOxygen > 0)
	{
		m_currentOxygen = m_currentOxygen + oxygen;
		m_oxygenPercent = m_currentOxygen / m_initialOxygen;
	}
	else
	{
		m_currentOxygen = 0.f;
		m_oxygenPercent = 0.f;
	}
	if (m_oxygenPercent < 0.2f)
	{
		m_oxygenWarning = m_oxygenPercent;
	}
	else
	{
		m_oxygenWarning = 0.f;
	}
	m_initialOxygenString = FString::FromInt((int)m_initialOxygen);
	m_currentOxygenString = FString::FromInt((int)m_currentOxygen);
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
	for (auto& eachItem : ShowInventory)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Item: %s "), *eachItem));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("End of Inventory"));
}
