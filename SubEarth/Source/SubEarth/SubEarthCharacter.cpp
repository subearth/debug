// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SubEarth.h"
#include "SubEarthCharacter.h"
#include "SubEarthProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ASubEarthCharacter

/******************************************************************************/
ASubEarthCharacter::ASubEarthCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	Mesh1P->SetHiddenInGame(true, true);

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(RootComponent);

	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->Hand = EControllerHand::Left;
	L_MotionController->SetupAttachment(RootComponent);

	
	leftHand = CreateDefaultSubobject<UHand>(TEXT("LeftHand"));
	USceneComponent* lhs = leftHand->GetHandSceneComponent();
	lhs->SetupAttachment(RootComponent);
	lhs->RelativeLocation = FVector(120.0f, -25.0f, -5.0f);

	rightHand = CreateDefaultSubobject<UHand>(TEXT("RightHand"));
	USceneComponent* rhs = rightHand->GetHandSceneComponent();
	rhs->SetupAttachment(RootComponent);
	rhs->RelativeLocation = FVector(120.0f, 25.0f, -5.0f);	
	
}

/******************************************************************************/
void ASubEarthCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("ASubEarthCharacter started"));

}

/******************************************************************************/
void ASubEarthCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASubEarthCharacter::OnResetVR);

	PlayerInputComponent->BindAction("LeftHandToggleGrab", IE_Pressed, this, &ASubEarthCharacter::LeftHandToggleGrab);
	PlayerInputComponent->BindAction("LeftHandToggleGrab", IE_Released, this, &ASubEarthCharacter::LeftHandToggleGrab);

	PlayerInputComponent->BindAction("RightHandToggleGrab", IE_Pressed, this, &ASubEarthCharacter::RightHandToggleGrab);
	PlayerInputComponent->BindAction("RightHandToggleGrab", IE_Released, this, &ASubEarthCharacter::RightHandToggleGrab);

	PlayerInputComponent->BindAction("LeftHandButton1", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton1);
	PlayerInputComponent->BindAction("LeftHandButton2", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton2);
	PlayerInputComponent->BindAction("LeftHandButton3", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton3);
	PlayerInputComponent->BindAction("LeftHandButton4", IE_Pressed, this, &ASubEarthCharacter::LeftHandButton4);

	PlayerInputComponent->BindAction("RightHandButton1", IE_Pressed, this, &ASubEarthCharacter::RightHandButton1);
	PlayerInputComponent->BindAction("RightHandButton2", IE_Pressed, this, &ASubEarthCharacter::RightHandButton2);
	PlayerInputComponent->BindAction("RightHandButton3", IE_Pressed, this, &ASubEarthCharacter::RightHandButton3);
	PlayerInputComponent->BindAction("RightHandButton4", IE_Pressed, this, &ASubEarthCharacter::RightHandButton4);


	PlayerInputComponent->BindAxis("MoveForward", this, &ASubEarthCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubEarthCharacter::MoveRight);



	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASubEarthCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASubEarthCharacter::LookUpAtRate);
	UE_LOG(LogTemp, Log, TEXT("Binding Complete"));
}

/******************************************************************************/
void ASubEarthCharacter::LeftHandButton1()
{
	leftHand->PressButton1();
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
	if (leftHand->IsGrabbing())
	{
		leftHand->SetGrabbing(false);
	}
	else
	{
		leftHand->SetGrabbing(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Left Hand isEmpty: %d"), leftHand->IsHandEmpty());
}

/******************************************************************************/
void ASubEarthCharacter::RightHandToggleGrab()
{
	if (rightHand->IsGrabbing())
	{
		rightHand->SetGrabbing(false);
	}
	else
	{
		rightHand->SetGrabbing(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Right Hand isEmpty: %d"), rightHand->IsHandEmpty());
}

/******************************************************************************/
void ASubEarthCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
	UE_LOG(LogTemp, Log, TEXT("VR was reset"));
}

/******************************************************************************/
void ASubEarthCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

/******************************************************************************/
void ASubEarthCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

/******************************************************************************/
void ASubEarthCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

/******************************************************************************/
void ASubEarthCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

