// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameHUD.h"
#include "Widgets/SWeakWidget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	// 2. Spawn & show slate
	// ShowSettingsWidget();

	// 3. Spawn & show UMG
	SpawnGameMenuWidget();
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!CrosshairTexture) return;

	// Canvas
	float CanvasWidth = Canvas->ClipX;
	float CanvasHeight = Canvas->ClipY;
	FVector2D Center(CanvasWidth * 0.5f, CanvasHeight * 0.5f);

	// Crosshair
	float CrosshairWidth = CrosshairTexture->GetSurfaceWidth();
	float CrosshairHeight = CrosshairTexture->GetSurfaceHeight();

	float AlignmentX = 0.5f;
	float AlignmentY = 0.5f;
	FVector2D CrosshairPosOffset(CrosshairWidth * AlignmentX, CrosshairHeight * AlignmentY);

	// Draw Settings
	FVector2D CrosshairDrawPos = Center - CrosshairPosOffset;

	float CrosshairScale = 5.0f;
	FVector2D CrosshairDrawSize(CrosshairWidth * CrosshairScale, CrosshairHeight * CrosshairScale);

	// Draw the crosshair
	FCanvasTileItem CrosshairTileItem(CrosshairDrawPos, CrosshairTexture->GetResource(), CrosshairDrawSize, FLinearColor::White);
	CrosshairTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(CrosshairTileItem);
}

void AGameHUD::ShowSettingsWidget()
{
	SettingsWidget = SNew(SSettingsWidget).MyInt(6548).GameHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(SettingsWidgetContainer, SWeakWidget).PossiblyNullContent(SettingsWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void AGameHUD::HideSettingsWidget()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(SettingsWidgetContainer.ToSharedRef());

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AGameHUD::SpawnGameMenuWidget()
{
	if (!GameMenuWidgetClass) return;

	// Delete game menu widget if it already exists
	if (GameMenuWidgetContainer) {
		GameMenuWidgetContainer->RemoveFromParent();
		GameMenuWidgetContainer = nullptr;
	}

	GameMenuWidgetContainer = CreateWidget<UGameMenuWidget>(GetWorld(), GameMenuWidgetClass);
	GameMenuWidgetContainer->AddToViewport();

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}
