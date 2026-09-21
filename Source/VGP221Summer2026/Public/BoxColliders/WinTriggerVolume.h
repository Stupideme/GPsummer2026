#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinTriggerVolume.generated.h"

class UBoxComponent;
class UPrimitiveComponent;
class UUserWidget;

// TODO: Replace with the actual C++ class that BP_Player inherits from.
// (You can't Cast<> directly to a Blueprint-only class from C++; you need
// its native parent class, or use LoadClass/StaticLoadClass with the BP's
// generated class path.)
class ABasePlayerCharacter;

// TODO: Replace with the actual C++ class that Timer_HUD inherits from.
class ATimerHUD;

/**
 * C++ equivalent of the "On Component Begin Overlap (Box)" blueprint graph:
 * detects the player, shows a win message, stops the timer HUD, disables
 * player movement input, and adds a "Win" widget to the viewport.
 */
UCLASS()
class YOURGAME_API AWinTriggerVolume : public AActor
{
	GENERATED_BODY()

public:
	AWinTriggerVolume();

protected:
	virtual void BeginPlay() override;

	// The overlap volume (equivalent to the Box component in the blueprint)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Win Trigger")
	UBoxComponent* CollisionBox;

	// Widget class to spawn when the player wins.
	// This corresponds to the "Class" pin on "Create Win Screen Widget".
	// Set this in the editor (Class Defaults) to your actual win-screen widget BP.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Win Trigger")
	TSubclassOf<UUserWidget> WinWidgetClass;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
