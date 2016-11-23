// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "PocketComponent.h"
#include "CharacterControl/SubEarthCharacter.h"
#include "HUD/SubEarthHUD.h"


/******************************************************************************/
UPocketComponent::UPocketComponent()
{
	m_interactableComponentType = POCKET;
	m_pickupInPocket = NULL;
	m_isPocketEmpty = true;

	m_objectCollider->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	m_objectCollider->bHiddenInGame = false;
}

/******************************************************************************/
void UPocketComponent::ExecutePrimaryAction(APickup* pickup)
{
	UE_LOG(LogTemp, Log, TEXT("UPocketComponent::ExecutePrimaryAction"));
}

/******************************************************************************/
bool UPocketComponent::IsPocketEmpty()
{
	return m_isPocketEmpty;
}

/******************************************************************************/
APickup* UPocketComponent::TakeItemOutOfPocket(void)
{
	APickup* pickup = NULL;

	if (!m_isPocketEmpty && m_pickupInPocket != NULL)
	{
		pickup = m_pickupInPocket;
		pickup->DetachRootComponentFromParent();
		pickup->SetDefaultInHandOrientation();
		pickup->SetActorEnableCollision(true);

		m_pickupInPocket = NULL;
		m_isPocketEmpty = true;

		UE_LOG(LogTemp, Log, TEXT("Took %s out of pocket"), *pickup->GetName());
	}

	return pickup;
}

/******************************************************************************/
void UPocketComponent::PlaceItemInPocket(APickup* pickup)
{
	if (m_isPocketEmpty)
	{
		m_pickupInPocket = pickup;
		m_isPocketEmpty = false;

		pickup->AttachToComponent(m_objectRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		pickup->SetDefaultWorldOrientation(); // TODO this create orientation for "In Pocket"
		pickup->SetActorEnableCollision(false);

		ASubEarthHUD* hud = Cast<ASubEarthHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

		InventoryMap.Add(*pickup->GetName(), pickup->Icon);
		UE_LOG(LogTemp, Log, TEXT("Placed %s in pocket"), *pickup->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add %s to the pocket when the pocket is not empty!"), *pickup->GetName());
	}
}

/******************************************************************************/
FString UPocketComponent::GetNameOfPickupInPocket(void)
{
	FString str = "EMPTY";

	if (m_pickupInPocket != NULL)
	{
		str = m_pickupInPocket->GetName();
	}

	return str;
}
