// Fill out your copyright notice in the Description page of Project Settings.

#include "SubEarth.h"
#include "SubEarthHUD.h"
#include "CharacterControl/SubEarthCharacter.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ASubEarthHUD::ASubEarthHUD()
{
	////MyPlayerController = Cast<ASubEarthCharacter>(Player);
	//ASubEarthCharacter* p_Player = Cast<ASubEarthCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	//// Empty

	//static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/Assets/Textures/FirstPersonCrosshair"));
	//CrosshairTex = CrosshiarTexObj.Object;
}


void ASubEarthHUD::DrawHUD()
{
	Super::DrawHUD();

	//if (p_Player->IsActorInitialized())
	//{
	//	float currentOxygen = p_Player->GetCurrentOxygen();
	//	float initialOxygen = p_Player->GetInitialOxygen();

	//	// Draw very simple crosshair

	//	// find center of the Canvas
	//	float ratio = currentOxygen / initialOxygen;
	//	//const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	//	const FVector2D Center(Canvas->ClipX * ratio, Canvas->ClipY * 0.5f);

	//	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	//	const FVector2D CrosshairDrawPosition((Center.X),
	//		(Center.Y));

	//	// draw the crosshair
	//	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//	TileItem.BlendMode = SE_BLEND_Translucent;
	//	Canvas->DrawItem(TileItem);
	//}
	
	
}


