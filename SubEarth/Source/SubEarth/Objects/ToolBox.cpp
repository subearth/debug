// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "ToolBox.h"


/******************************************************************************/
AToolBox::AToolBox()
{
	m_interactableType = TOOL_BOX;
	m_isClosed = true;
	m_animState = NOT_ANIMATING;

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

	m_objectCollider->bGenerateOverlapEvents = true;
	m_objectCollider->OnComponentBeginOverlap.AddDynamic(this, &AToolBox::OpenBox);
	m_objectCollider->OnComponentEndOverlap.AddDynamic(this, &AToolBox::CloseBox);

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
	if (m_isClosed)
	{
		m_animState = OPENING;
		m_isClosed = false;
		EnableAnimation();
	}
	else
	{
		m_animState = CLOSING;
		m_isClosed = true;
		EnableAnimation();
	}
}

/******************************************************************************/
void AToolBox::ExecuteAnimation(float delta_time)
{
	const float OPEN_RATE = 50.0f; // a little more than 1 second
	const float CLOSE_RATE = 70.0f; // 70 = 1 sec
	const float X_OPEN_POSITION = 70.0;
	const float X_CLOSE_POSITION = 0.0f;

	static float x_rot = X_CLOSE_POSITION;

	switch (m_animState)
	{
		case NOT_ANIMATING:
		{
			// Do nothing
			break;
		}
		case OPENING:
		{
			x_rot += (OPEN_RATE * delta_time);

			if (x_rot >= X_OPEN_POSITION)
			{
				x_rot = X_OPEN_POSITION;
				m_animState = NOT_ANIMATING;
				DisableAnimation();
			}
			break;
		}
		case CLOSING:
		{
			x_rot -= (CLOSE_RATE * delta_time);

			if (x_rot <= X_CLOSE_POSITION)
			{
				x_rot = X_CLOSE_POSITION;
				m_animState = NOT_ANIMATING;
				DisableAnimation();
			}
			break;
		}
	}

	m_hingeSceneNode->SetRelativeRotation(FRotator(x_rot, 0.f, 0.f));
}
/***************************************************************************/
void AToolBox::OpenBox(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{
	FRotator B = FRotator(70.0f, 0.0f, 0.0f);
	if (otherActor->IsA(ASubEarthCharacter::StaticClass())) 
	{
		FRotator C1 = FMath::Lerp(m_hingeSceneNode->RelativeRotation, B, 0.05f);
		m_hingeSceneNode->SetRelativeRotation(C1);
	}
}


void AToolBox::CloseBox(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex) 
{

}
