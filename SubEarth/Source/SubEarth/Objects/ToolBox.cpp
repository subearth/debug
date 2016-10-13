// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "ToolBox.h"


/******************************************************************************/
AToolBox::AToolBox()
{
	m_interactableType = TOOL_BOX;
	m_isClosed = true;

	FString name = GetName();
	FString RootName = name + "HingeRoot";
	m_hingeSceneNode = CreateDefaultSubobject<USceneComponent>(*RootName);
	m_hingeSceneNode->SetupAttachment(m_objectRoot);
	m_hingeSceneNode->SetRelativeLocation(FVector(-25.f, 0.f, 0.f));

	// Setup the toolbox latch interactable size
	//m_objectCollider->DetachFromComponent();
	m_objectCollider->SetupAttachment(m_hingeSceneNode);
	m_objectCollider->SetRelativeLocation(FVector(55.f, 0.f, 0.f));
	m_objectCollider->SetWorldScale3D(FVector(0.1f, 0.4f, 0.1f));
	m_objectCollider->bHiddenInGame = false;
	
	// SEAN!!!! Don't delete this
	/*FString ColliderName = name + "HandAreaCollider";
	m_handAreaCollider = CreateDefaultSubobject<UBoxComponent>(FName(*ColliderName));
	m_handAreaCollider->SetupAttachment(m_hingeSceneNode);
	m_handAreaCollider->SetRelativeLocation(FVector(55.f, 0.f, -9.f));
	m_handAreaCollider->SetWorldScale3D(FVector(0.15f, 0.45f, 0.15f));
	m_handAreaCollider->bHiddenInGame = false;*/


	//m_objectMesh->DetachFromParent();
	m_objectMesh->SetupAttachment(m_hingeSceneNode);
	m_objectMesh->SetRelativeLocation(FVector(25.f, 0.f, 0.f));
	m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	m_objectMesh->SetRelativeScale3D(FVector(0.5f, 1.0f, 0.1f));
	m_objectMesh->bGenerateOverlapEvents = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> my_mesh(TEXT("StaticMesh'/Game/Assets/Objects/ToolBox/Shape_Cube.Shape_Cube'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> my_material(TEXT("Material'/Game/Assets/Objects/ToolBox/M_Wood_Oak.M_Wood_Oak'"));
	if (my_mesh.Object)
	{
		m_objectMesh->SetStaticMesh(my_mesh.Object);
		//m_objectMesh->SetMaterial(0, my_material.Object);
	}
}

/******************************************************************************/
void AToolBox::ExecutePrimaryAction(APickup* pickup)
{
	// TODO Animate opening the toolbox here.
	UE_LOG(LogTemp, Log, TEXT("AToolBox::ExecutePrimaryAction  OPENING TOOLBOX"));
	if (m_isClosed)
	{
		m_hingeSceneNode->SetRelativeRotation(FRotator(70.f, 0.f, 0.f));
		m_isClosed = false;
	}
	else
	{
		m_hingeSceneNode->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_isClosed = true;
	}
	
}

