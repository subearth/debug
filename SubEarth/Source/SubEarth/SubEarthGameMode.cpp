// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "SubEarthGameMode.h"
#include "HUD/SubEarthHUD.h"
#include "CharacterControl/SubEarthCharacter.h"

// HUD:
#include "Blueprint/UserWidget.h"

ASubEarthGameMode::ASubEarthGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/CharacterCPP/Blueprints/SubEarthCharacterBP"));
	
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	
	// use our custom HUD class
	HUDClass = ASubEarthHUD::StaticClass();
}

/* START HUD */
void ASubEarthGameMode::BeginPlay()
{
	Super::BeginPlay();

	ASubEarthCharacter* MyCharacter = Cast<ASubEarthCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	/*if (HUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}*/

	if (PlayerHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

/* END HUD */


