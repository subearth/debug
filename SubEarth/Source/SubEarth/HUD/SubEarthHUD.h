// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "SubEarthHUD.generated.h"

/**
 * 
 */
UCLASS()
class SUBEARTH_API ASubEarthHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ASubEarthHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	// Player component
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ASubEarthCharacter* p_Player;
	class UTexture2D* CrosshairTex;
	
	
};
