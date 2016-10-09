// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "OxygenTank.h"
#include "CharacterControl/SubEarthCharacter.h"


AOxygenTank::AOxygenTank() {

	//Constructor			
	IsOxygenTankPickedUp = false;
}

void AOxygenTank::GetOxygenTank() {

	//Update oxygen value here
//	ASubEarthCharacter* MyCharacter = Cast<ASubEarthCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
//	MyCharacter->m_currentOxygen += MyCharacter -> m_initialOxygen;

	IsOxygenTankPickedUp = true;
}


