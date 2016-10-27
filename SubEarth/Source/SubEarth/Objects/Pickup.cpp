// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "Objects/Pickup.h"

/******************************************************************************/
APickup::APickup()
{
	m_interactableType = PICKUP_OBJECT;

	// Enable the tick call back, but start with it disabled
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	m_objectCollider->OnComponentBeginOverlap.AddDynamic(this, &APickup::BeginOverlap);
	m_objectCollider->OnComponentEndOverlap.AddDynamic(this, &APickup::EndOverlap);
	// Set per pickup:
	m_floatMode = NONE;
	m_isFloating = false;
	m_floatSpeed = 1.f;
	m_floatRange = 1.f;
	m_floatDisplacement = 0.f;
	m_floatDirection = 1.f;
	m_firstTouched = NULL;
}

/******************************************************************************/
APickup::Pickup_e APickup::GetPickupType(void)
{
	return m_pickupType;
}

/******************************************************************************/
void APickup::ExecutePrimaryAction(APickup* pickup)
{
	// The default action upon trigger pull is for the hand to pick up the object. 
	// If the pickup needs a custom action, they must override this function
	UE_LOG(LogTemp, Log, TEXT("APickup::ExecutePrimaryAction  This function is meant to be overridden!"));
}

/******************************************************************************/
void APickup::SetDefaultInHandOrientation(void)
{
	// This is the default orientation of a Pickup. The derived class should overwrite this.
	m_objectRoot->RelativeRotation = FRotator(0.0f, 0.0f, 0.0f);
}

/******************************************************************************/
void APickup::SetDefaultWorldOrientation(void)
{
	// This is the default orientation of a Pickup. The derived class should overwrite this.
	m_objectRoot->RelativeRotation = FRotator(0.0f, 0.0f, 0.0f);
}

void APickup::Tick(float DeltaTime)
{
	// This function is turned off by default. The derived class can turn it on if 
	// animation is needed.
	Super::Tick(DeltaTime);
	if (m_isFloating)
	{
		ExecutePhysics(DeltaTime);
	}
	
}

void APickup::ExecutePhysics(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Physics is running."));
	switch (m_floatMode)
	{
	case SINK:
		// Sinking function:
		GetRootComponent()->AddWorldTransform(FTransform(FVector(0.f, 0.f, -m_floatSpeed * DeltaTime)));
		GetRootComponent()->AddWorldRotation(FRotator(rand() % m_floatRotate * DeltaTime, rand() % m_floatRotate * DeltaTime, rand() % m_floatRotate * DeltaTime));
		break;
	case FLOAT:
		// Sinking function:
		GetRootComponent()->AddWorldTransform(FTransform(FVector(0.f, 0.f, m_floatSpeed * DeltaTime)));
		GetRootComponent()->AddWorldRotation(FRotator(rand() % m_floatRotate * DeltaTime, rand() % m_floatRotate * DeltaTime, rand() % m_floatRotate * DeltaTime));
		break;
	case BOB:
		// Sinking function:
		m_floatDisplacement += m_floatSpeed * DeltaTime; 
		if (m_floatDisplacement > m_floatRange)
		{
			m_floatDirection *= -1.f;
			m_floatDisplacement = 0.f;
		}
		GetRootComponent()->AddWorldTransform(FTransform(FVector(0.f, 0.f, m_floatDirection * m_floatSpeed * DeltaTime)));
		GetRootComponent()->AddWorldRotation(FRotator(rand() % m_floatRotate * DeltaTime, rand() % m_floatRotate * DeltaTime, rand() % m_floatRotate * DeltaTime));
		break;
	}
}

void APickup::BeginOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("APickup::BeginOverlap  overlap begin"));
	//UGameplayStatics::OpenLevel(this, TEXT("World'/Game/maps/Tutorials_Level.Tutorial-Level"), false, NULL);
	//GetWorld()->ServerTravel("/Game/Maps/TutorialMap");

	m_isFloating = false;
	if (m_firstTouched == NULL)
	{
		m_firstTouched = otherActor;
		UE_LOG(LogTemp, Log, TEXT("APickup::BeginOverlap  first touched."));
	}
}

void APickup::EndOverlap(UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComponent,
	int32 otherBodyIndex)
{
	if (otherActor == m_firstTouched)
	{
		UE_LOG(LogTemp, Log, TEXT("APickup::EndOverlap  overlap end"));
		m_isFloating = true;
		m_firstTouched = NULL;
	}
}