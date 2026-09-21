// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "GUI/GameMenuWidget.h"
#include "GUI/SlateExample/SSettingsWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2026_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	// 1. HUD DRaw Method of making UI
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairTexture;

	// 2. Slates method of making UI
	TSharedPtr<class SSettingsWidget> SettingsWidget;
	TSharedPtr<class SWidget> SettingsWidgetContainer;

	void ShowSettingsWidget();
	void HideSettingsWidget();

	// 3. UMG method of making UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameMenuWidget> GameMenuWidgetClass;
	UGameMenuWidget* GameMenuWidgetContainer;

	void SpawnGameMenuWidget();
};
