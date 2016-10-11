// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "FlashLight.h"


/******************************************************************************/
AFlashLight::AFlashLight()
{
	//m_pickupType = OXYGEN_TANK;

	m_objectCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	m_objectCollider->SetWorldScale3D(FVector(0.4f, 0.1f, 0.1f));
	m_objectCollider->bHiddenInGame = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FlashlightMesh(TEXT("StaticMesh'/Game/Assets/Objects/Flashlight/FlashlightMesh1'"));
	if (FlashlightMesh.Object)
	{
		m_objectMesh->SetStaticMesh(FlashlightMesh.Object);

		m_objectMesh->SetRelativeLocation(FVector(5.f, 0.f, 0.f));
		m_objectMesh->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
		m_objectMesh->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	}

	m_spotLightName = GetName() + "SpotLight";
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(FName(*m_spotLightName));
	SpotLight->SetupAttachment(m_objectRoot);
	SpotLight->SetRelativeLocation(FVector(10.f, 0.f, 0.f));
	SpotLight->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
}

/******************************************************************************/
void AFlashLight::ExecuteAction1(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AFlashLight::ExecuteAction1"));
}

/******************************************************************************/
void AFlashLight::ExecuteAction2(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AFlashLight::ExecuteAction2"));
	SpotLight->SetVisibility(!SpotLight->bVisible);
}

/******************************************************************************/
void AFlashLight::ExecuteAction3(AInteractable* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("AFlashLight::ExecuteAction3"));
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


