// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/SlateExample/SSettingsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSettingsWidget::Construct(const FArguments& InArgs)
{
	MyInt = InArgs._MyInt;
	GameHUD = InArgs._GameHUD;

	const FMargin SettingsMargin(800.0f, 300.0f);

	// Title Settings
	const FText TitleText = FText::FromString("Settings Screen");
	FSlateFontInfo TitleFontInfo = FCoreStyle::Get().GetFontStyle("EmbassedText");
	TitleFontInfo.Size = 60;

	// Button Settings
	const FMargin ButtonMargin(10.f);
	FSlateFontInfo ButtonFontInfo = FCoreStyle::Get().GetFontStyle("EmbassedText");
	ButtonFontInfo.Size = 40;

	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FLinearColor::Black)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(SettingsMargin)
		[
			SNew(SVerticalBox)
			// Title Text
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text(TitleText)
				.Font(TitleFontInfo)
				.Justification(ETextJustify::Center)
			]
			// Resume Button
			+SVerticalBox::Slot()
			.Padding(ButtonMargin)
			[
				SNew(SButton)
				.OnClicked(this, &SSettingsWidget::OnResumeClicked)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Resume"))
					.Font(ButtonFontInfo)
					.Justification(ETextJustify::Center)
				]
			]
			// Int Button
			+ SVerticalBox::Slot()
			.Padding(ButtonMargin)
			[
				SNew(SButton)
				.OnClicked(this, &SSettingsWidget::OnIntClicked)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Int"))
					.Font(ButtonFontInfo)
					.Justification(ETextJustify::Center)
				]
			]
			// Quit Button
			+ SVerticalBox::Slot()
			.Padding(ButtonMargin)
			[
				SNew(SButton)
				.OnClicked(this, &SSettingsWidget::OnQuitClicked)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Quit"))
					.Font(ButtonFontInfo)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];
	
}
FReply SSettingsWidget::OnResumeClicked() const
{
	if(GameHUD.IsValid())
	{
		GameHUD->HideSettingsWidget();
	}

	return FReply::Handled();
}
FReply SSettingsWidget::OnIntClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("MyInt: %d"), MyInt);
	return FReply::Handled();
}
FReply SSettingsWidget::OnQuitClicked() const
{
	if(GameHUD.IsValid())
	{
		GameHUD->PlayerOwner->ConsoleCommand("quit");
	}

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
