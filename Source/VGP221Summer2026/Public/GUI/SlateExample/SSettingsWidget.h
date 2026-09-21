// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/GameHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class VGP221SUMMER2026_API SSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, GameHUD)
	SLATE_ARGUMENT(int, MyInt)
	SLATE_END_ARGS()

	int MyInt; 
	TWeakObjectPtr<class AGameHUD> GameHUD;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnResumeClicked() const;
	FReply OnIntClicked() const;
	FReply OnQuitClicked() const;

	/*
		Smart Pointers

		Unique Pointers: UnqiuePtr<T> = UniquePtr<int> score
			- Sole owner of the object
			- Cannot be copied, only moved
			- Automatically deletes the object when it goes out of scope
			- Eg. ScoreManager

		Shared Pointers: SharedPtr<T> = SharedPtr<int> PlayerHealth
			- Multiple ownership of the object it points to
			- Can be copied and shared among multiple owners
			- Automatically deletes the object when the last owner goes out of scope
			- Eg. UI widgets, game objects shared across multiple systems(Eg. Character health. UI might use it)

		Weak Pointers: WeakPtr<T> = WeakPtr<Enemy> EnemyTarget
			- Non-owning reference to an object managed by a shared pointer
			- Doesn't affect the reference count of the shared pointer
			- Can be used break ciricular references
			- Must be converted to a shared pointer before use
			- Eg. Targeting system, where you want to reference an enemy without preventing it from being destroyed

		Soft Object Pointers: SoftObjectPtr<T> = SoftObjectPtr<UStaticMesh> HugeCity
			- References an object that may not be loaded in memory
			- Load assets on demand, reducing memory usage and improving performance
			- Eg. Large open-world games, where you want to reference assets that may not be loaded yet
	*/
};
