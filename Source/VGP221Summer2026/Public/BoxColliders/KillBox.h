#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillBox.generated.h"

class UBoxComponent;
class UPrimitiveComponent;

// TODO: Replace with the actual C++ class that BP_Player inherits from.
// (You can't Cast<> directly to a Blueprint-only class from C++; you need
// its native parent class, or use LoadClass/StaticLoadClass with the BP's
// generated class path.)
class ABasePlayerCharacter;

/**
 * C++ equivalent of the "On Component Begin Overlap (Box)" blueprint graph:
 * if the overlapping actor is the player, open a new level (e.g. a
 * "you died" / restart map); otherwise print a debug message.
 */
UCLASS()
class YOURGAME_API AKillBox : public AActor
{
	GENERATED_BODY()

public:
	AKillBox();

protected:
	virtual void BeginPlay() override;

	// The overlap volume (equivalent to the Box component in the blueprint)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kill Box")
	UBoxComponent* CollisionBox;

	// Level to open when the player enters the kill box.
	// Corresponds to the "Level Name" pin on "Open Level (by Name)".
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Box")
	FName LevelToOpen = TEXT("Gamemap");

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
