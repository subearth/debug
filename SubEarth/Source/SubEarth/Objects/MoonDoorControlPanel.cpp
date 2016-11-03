// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "MoonDoorControlPanel.h"

/******************************************************************************/
AMoonDoorControlPanel::AMoonDoorControlPanel()
{
	m_interactableType = MOON_DOOR_CONTROL_PANEL;
	m_animState = NOT_ANIMATING;
	m_isClosed = true;

	//// Hide this collider.
	//m_objectCollider->bHiddenInGame = true;
	//m_objectCollider->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	FString name = GetName();

	// Setup the control panel
	FString ctrl_name = name + "ControlPanel";
	m_ctrlPanel = CreateDefaultSubobject<USceneComponent>(*ctrl_name);
	m_ctrlPanel->SetupAttachment(m_objectRoot);
	m_ctrlPanel->SetRelativeLocation(FVector(-150.f, 0.f, 0.f));

	// Setup the left moon door
	FString left_moon_name = name + "LeftMoonDoor";
	m_LeftDoor = CreateDefaultSubobject<USceneComponent>(*left_moon_name);
	m_LeftDoor->SetupAttachment(m_objectRoot);
	m_LeftDoor->SetRelativeLocation(FVector(-50.5f, 0.f, 0.f));

	// Setup the right moon door
	FString right_moon_name = name + "RightMoonDoor";
	m_RightDoor = CreateDefaultSubobject<USceneComponent>(*right_moon_name);
	m_RightDoor->SetupAttachment(m_objectRoot);
	m_RightDoor->SetRelativeLocation(FVector(50.5f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> left_mesh(TEXT("StaticMesh'/Game/Assets/Objects/ToolBox/Shape_Cube.Shape_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> right_mesh(TEXT("StaticMesh'/Game/Assets/Objects/ToolBox/Shape_Cube.Shape_Cube'"));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ctrl_panel_mesh(TEXT("StaticMesh'/Game/Assets/Objects/ToolBox/Shape_Cube.Shape_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ctrl_panel_mesh(TEXT("StaticMesh'/Game/Assets/Objects/ControlPanels/control_panel_1__final.control_panel_1__final'"));

	if (left_mesh.Object != NULL && right_mesh.Object != NULL && ctrl_panel_mesh.Object != NULL)
	{
		// Setup the left moon door mesh
		m_ctrlPanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ControlPanelMesh"));
		m_ctrlPanelMesh->SetStaticMesh(ctrl_panel_mesh.Object);
		m_ctrlPanelMesh->SetupAttachment(m_ctrlPanel);
		m_ctrlPanelMesh->bGenerateOverlapEvents = false;

		FString ColliderName = name + "Collider2";
		m_objectCollider2 = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
		m_objectCollider2->SetupAttachment(m_ctrlPanelMesh);
		m_objectCollider2->SetWorldScale3D(FVector(0.75f, 0.40f, 0.1f));
		m_objectCollider2->SetRelativeLocation(FVector(-235.0f, 65.f, 55.0f));
		m_objectCollider2->bHiddenInGame = false;

		// Setup the left moon door mesh
		m_leftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMoonDoorMesh"));
		m_leftDoorMesh->SetStaticMesh(left_mesh.Object);
		m_leftDoorMesh->SetupAttachment(m_LeftDoor);
		m_leftDoorMesh->SetWorldScale3D(FVector(1.0f, 2.0f, 0.05f));
		m_leftDoorMesh->bGenerateOverlapEvents = false;

		// Setup the right moon door mesh
		m_rightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMoonDoorMesh"));
		m_rightDoorMesh->SetStaticMesh(right_mesh.Object);
		m_rightDoorMesh->SetupAttachment(m_RightDoor);
		m_rightDoorMesh->SetWorldScale3D(FVector(1.0f, 2.0f, 0.05f));
		m_rightDoorMesh->bGenerateOverlapEvents = false;
	}
}

/******************************************************************************/
void AMoonDoorControlPanel::ExecutePrimaryAction(APickup* pickup)
{
	if (m_isClosed)
	{
		UE_LOG(LogTemp, Log, TEXT("AMoonDoorControlPanel::ExecutePrimaryAction OPENING"));
		m_animState = OPENING;
		m_isClosed = false;
		EnableAnimation();

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AMoonDoorControlPanel::ExecutePrimaryAction CLOSING"));
		m_animState = CLOSING;
		m_isClosed = true;
		EnableAnimation();
	}
}

/******************************************************************************/
void AMoonDoorControlPanel::ExecuteAnimation(float delta_time)
{
	const float OPEN_RATE = 50.0f;
	const float CLOSE_RATE = 50.0f;
	const float X_OPEN_POSITION = 150.0;
	const float X_CLOSE_POSITION = 50.5f;

	static float x = X_CLOSE_POSITION;

	switch (m_animState)
	{
	case NOT_ANIMATING:
	{
		// Do nothing
		break;
	}
	case OPENING:
	{
		x += (OPEN_RATE * delta_time);

		if (x >= X_OPEN_POSITION)
		{
			x = X_OPEN_POSITION;
			m_animState = NOT_ANIMATING;
			DisableAnimation();
		}
		break;
	}
	case CLOSING:
	{
		x -= (CLOSE_RATE * delta_time);

		if (x <= X_CLOSE_POSITION)
		{
			x = X_CLOSE_POSITION;
			m_animState = NOT_ANIMATING;
			DisableAnimation();
		}
		break;
	}
	}

	UE_LOG(LogTemp, Log, TEXT("AMoonDoorControlPanel::ExecuteAnimation %f"), x);

	m_LeftDoor->SetRelativeLocation(FVector(-x, 0.f, 0.f));
	m_RightDoor->SetRelativeLocation(FVector(x, 0.f, 0.f));
}
