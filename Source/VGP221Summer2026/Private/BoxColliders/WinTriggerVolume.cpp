#include "WinTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "Engine/Engine.h"

// TODO: point these at your real headers
#include "BasePlayerCharacter.h"   // native parent class of BP_Player
#include "TimerHUD.h"              // native parent class of Timer_HUD

AWinTriggerVolume::AWinTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
}

void AWinTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	// Equivalent of the red "On Component Begin Overlap (Box)" event node
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWinTriggerVolume::OnOverlapBegin);
}

void AWinTriggerVolume::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// "Cast To BP_Player" + "Is Valid"
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(OtherActor);

	if (IsValid(Player))
	{
		// Print Text "YOU WIN"
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("YOU WIN"));
		}

		// "Get Player Controller" (index 0)
		APlayerController* PC = Cast<APlayerController>(Player->GetController());
		if (PC)
		{
			// "Get HUD" -> "Cast To Timer_HUD"
			ATimerHUD* TimerHUD = Cast<ATimerHUD>(PC->GetHUD());
			if (TimerHUD)
			{
				// "SET" node: sets the Win flag on the HUD.
				// TODO: confirm the exact property name/type on your HUD class.
				TimerHUD->Win = true;

				// The blueprint's SET node also wired a "TimeWidget" pin.
				// TODO: assign it here if you still need that reference, e.g.:
				// TimerHUD->TimeWidget = SomeWidgetReference;
			}

			// "Set Ignore Move Input"
			PC->SetIgnoreMoveInput(true);

			// "Create Win Screen Widget" -> "Add to Viewport"
			if (WinWidgetClass)
			{
				UUserWidget* WinWidget = CreateWidget<UUserWidget>(PC, WinWidgetClass);
				if (WinWidget)
				{
					WinWidget->AddToViewport(0); // ZOrder 0
				}
			}
		}

		// Print Text "Timer Stopped"
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Timer Stopped"));
		}
	}
	else
	{
		// "Is Not Valid" branch -> Print Text "why no ref"
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("why no ref"));
		}
	}
}
