// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SubEarth.h"
#include "SubEarthGameMode.h"
#include "SubEarthHUD.h"
#include "SubEarthCharacter.h"

ASubEarthGameMode::ASubEarthGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASubEarthHUD::StaticClass();
}
