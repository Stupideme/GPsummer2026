#include "KillBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// TODO: point this at your real header
#include "BasePlayerCharacter.h" // native parent class of BP_Player

AKillBox::AKillBox()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
}

void AKillBox::BeginPlay()
{
	Super::BeginPlay();

	// Equivalent of the red "On Component Begin Overlap (Box)" event node
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AKillBox::OnOverlapBegin);
}

void AKillBox::OnOverlapBegin(
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
		// "Open Level (by Name)"
		UGameplayStatics::OpenLevel(this, LevelToOpen);
	}
	else
	{
		// "Is Not Valid" branch -> Print Text "NOT KILLING"
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NOT KILLING"));
		}
	}
}
