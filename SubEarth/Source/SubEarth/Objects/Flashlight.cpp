// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Flashlight.h"


AFlashlight::AFlashlight()
{
	//m_objectRoot
	m_light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	m_light->SetupAttachment(m_objectRoot);
	m_light->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	m_light->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}

// Inherited. See parent for description
void AFlashlight::ExecuteAction1(void) 
{
	m_light->SetIntensity(0);
	m_light->SourceRadius += 1.f;
}
void AFlashlight::ExecuteAction2(void) 
{
	//m_light->bIsActive = !m_light->bIsActive;
	//m_light->bVisible = !m_light->bVisible;
	m_light->ToggleVisibility("Light");

	UE_LOG(LogTemp, Log, TEXT("AFlashlight::ExecuteAction2, %d"), m_light->bVisible);
}
void AFlashlight::ExecuteAction3(void) 
{
	m_light->SetIntensity(10000);
	m_light->SourceRadius -= 1.f;
}

// Inherited. See parent for description
void AFlashlight::SetDefaultInHandOrientation(void) 
{
	
}

// Inherited. See parent for description
void AFlashlight::SetDefaultWorldOrientation(void) 
{

}

