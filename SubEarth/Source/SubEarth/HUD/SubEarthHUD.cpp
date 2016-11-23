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

	static ConstructorHelpers::FObjectFinder<UFont> HUDFontObj(TEXT("/Game/Assets/Textures/OpenSans"));
	HUDFont = HUDFontObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> HammerTexObj(TEXT("Texture2D'/Game/Assets/Icons/Hammer'"));
	HammerIcon = HammerTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> PliersTexObj(TEXT("Texture2D'/Game/Assets/Icons/Pliers'"));
	PliersIcon = PliersTexObj.Object;


}


void ASubEarthHUD::DrawHUD()
{
	Super::DrawHUD();

	//UE_LOG(LogTemp, Log, TEXT("HUD Display Check"));

	//if (p_Player->IsActorInitialized())
	//{
//		float currentOxygen = p_Player->GetCurrentOxygen();
//		float initialOxygen = p_Player->GetInitialOxygen();

	//	// Draw very simple crosshair

	//	 find center of the Canvas
//		float ratio = currentOxygen / initialOxygen;
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		const FVector2D RightDown(Canvas->ClipX * 0.8f, Canvas->ClipY * 0.8f);
		const FVector2D RightUp(Canvas->ClipX * 0.8f, Canvas->ClipY * 0.1f);
		const FVector2D LeftDown(Canvas->ClipX * 0.1f, Canvas->ClipY * 0.8f);


	//	const FVector2D Center(Canvas->ClipX * ratio, Canvas->ClipY * 0.5f);

	//	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		//const FVector2D CrosshairDrawPosition((Center.X),
		//							   		  (Center.Y));

	//	// draw the crosshair
		//FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
		//TileItem.BlendMode = SE_BLEND_Translucent;
		//Canvas->DrawItem(TileItem);
	

		ASubEarthCharacter* MyCharacter = Cast<ASubEarthCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		FString PowerLevelString = FString::Printf(TEXT("%10.1f"), FMath::Abs(MyCharacter->m_currentOxygen));
	//	DrawText(PowerLevelString, FColor::White, Center.X, Center.Y, HUDFont);
		//DrawText(PowerLevelString, FColor::White, 200, 70, HUDFont);

		//DrawRect(FColor::Green, 50, 50, MyCharacter->m_currentOxygen, 20.0f);

		if (MyCharacter->m_currentOxygen == 0)
			//DrawText("GAME OVER", FColor::Red, Center.X, Center.Y, HUDFont);

		FString Inventory1 = FString::Printf(TEXT("Right Down"));
		FString Inventory2 = FString::Printf(TEXT("Right Up"));
		FString Inventory3 = FString::Printf(TEXT("Left Down"));

		/*DrawText(Inventory1, FColor::White, RightDown.X, RightDown.Y, HUDFont);
		DrawText(Inventory2, FColor::White, RightUp.X, RightUp.Y, HUDFont);
		DrawText(Inventory3, FColor::White, LeftDown.X, LeftDown.Y, HUDFont);*/


}
	


