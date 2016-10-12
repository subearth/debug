// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "ToolBox.h"


/******************************************************************************/
AToolBox::AToolBox()
{
	m_interactableType = TOOL_BOX;

	// Setup the toolbox latch interactable size
	m_objectCollider->SetWorldScale3D(FVector(1.0f, 2.0f, 0.2f));
	m_objectCollider->SetRelativeLocation(FVector(0.f, 0.f, 1.0f));
	m_objectCollider->bHiddenInGame = false;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> my_mesh(TEXT("StaticMesh'/Game/Assets/Objects/ToolBox/Shape_Cube.Shape_Cube'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> my_material(TEXT("Material'/Game/Assets/Objects/ToolBox/M_Wood_Oak.M_Wood_Oak'"));

	if (my_mesh.Object)
	{
		m_objectMesh->SetStaticMesh(my_mesh.Object);
		//m_objectMesh->SetMaterial(0, my_material.Object);
		m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(0.5f, 1.0f, 0.5f));
	}
}

/******************************************************************************/
void AToolBox::ExecutePrimaryAction(APickup* pickup)
{
	// TODO Animate opening the toolbox here.
	UE_LOG(LogTemp, Log, TEXT("AToolBox::ExecutePrimaryAction  OPENING TOOLBOX"));

}

