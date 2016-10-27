// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "FlashLight.h"


/******************************************************************************/
AFlashLight::AFlashLight()
{
	m_floatMode = BOB;
	m_isFloating = true;
	m_floatSpeed = 3.f;
	m_floatRotate = 8.f;
	m_floatRange = 200.f;
	m_floatDisplacement = 0.f;
	PrimaryActorTick.SetTickFunctionEnable(true);

	//m_pickupType = OXYGEN_TANK;
	m_minAngle = 20.f;
	m_deltaAngle = 60.f;
	m_minRadius = 1000.f;
	m_deltaRadius = 14000.f;
	m_zoomPercent = 0.5;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FlashlightMesh(TEXT("StaticMesh'/Game/Assets/Objects/Flashlight/FlashlightMesh2'"));
	if (FlashlightMesh.Object)
	{
		m_objectMesh->SetStaticMesh(FlashlightMesh.Object);
		m_objectMesh->SetupAttachment(m_objectRoot);
		m_objectMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(180.f, 0.f, -90.f));
		m_objectMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));

		m_objectCollider->SetupAttachment(m_objectRoot);
		m_objectCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_objectCollider->SetWorldScale3D(FVector(1.f, 0.25f, 0.25f));
		m_objectCollider->bHiddenInGame = false;
		/*FString profileName = "OverlapAll";
		m_objectCollider->SetCollisionProfileName(FName(*profileName));*/

		m_spotLightName = GetName() + "SpotLight";
		SpotLight = CreateDefaultSubobject<USpotLightComponent>(FName(*m_spotLightName));
		
		SpotLight->SetupAttachment(m_objectRoot);
		SpotLight->SetRelativeLocation(FVector(17.f, 0.f, 0.f));
		SpotLight->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		SpotLight->SetAttenuationRadius(m_minRadius + (m_zoomPercent * m_deltaRadius));
		SpotLight->SetOuterConeAngle(m_minAngle + (m_zoomPercent * m_deltaAngle));
		SpotLight->SetLightColor(FLinearColor(255, 255, 255));
	}

	

	
}

/******************************************************************************/
void AFlashLight::ExecuteAction1(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AFlashLight::ExecuteAction1"));
	if (m_zoomPercent < 0.9f)
	{
		m_zoomPercent += 0.1f;
		SpotLight->SetAttenuationRadius(m_minRadius + (m_zoomPercent * m_deltaRadius));
		SpotLight->SetOuterConeAngle(m_minAngle + (m_zoomPercent * m_deltaAngle));
	}
	
}

/******************************************************************************/
void AFlashLight::ExecuteAction2(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AFlashLight::ExecuteAction2"));
	SpotLight->SetVisibility(!SpotLight->bVisible);

	GetWorld()->ServerTravel("/Game/Maps/TutorialMap");
}

/******************************************************************************/
void AFlashLight::ExecuteAction3(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AFlashLight::ExecuteAction3"));
	if (m_zoomPercent > 0.1f)
	{
		m_zoomPercent -= 0.1f;
		SpotLight->SetAttenuationRadius(m_minRadius + (m_zoomPercent * m_deltaRadius));
		SpotLight->SetOuterConeAngle(m_minAngle + (m_zoomPercent * m_deltaAngle));
	}
}

/******************************************************************************/
void AFlashLight::SetDefaultInHandOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//m_objectRoot->RelativeRotation = FRotator(21.0f, 10.5f, 50.5f);
}

/******************************************************************************/
void AFlashLight::SetDefaultWorldOrientation(void)
{
	m_objectRoot->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//m_objectRoot->RelativeRotation = FRotator(-21.0f, -10.5f, -50.5f);
}


