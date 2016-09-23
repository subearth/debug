// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SubEarthGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API ASubEarthGameMode : public AGameMode
{
	GENERATED_BODY()
	
		virtual void BeginPlay() override; // Override beginplay from the base class

public:
	ASubEarthGameMode();

	/* START HUD */
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OxygenTank", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget>PlayerHUDClass;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
	/* END HUD*/
};
