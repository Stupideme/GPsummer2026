// Fill out your copyright notice in the Description page of Project Settings.

#include "WinTrigger.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AWinTrigger::AWinTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BoxCollision->SetBoxExtent(BoxExtent);

	// Pure trigger: query only, overlap on everything, no physical blocking
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollision->SetGenerateOverlapEvents(true);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWinTrigger::OnOverlapBegin);
}

void AWinTrigger::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->SetBoxExtent(BoxExtent);
}

void AWinTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bHasTriggered)
	{
		return;
	}

	// Only trigger on the player character, not any random overlapping actor
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!PlayerCharacter || !PlayerCharacter->IsPlayerControlled())
	{
		return;
	}

	bHasTriggered = true;

	UE_LOG(LogTemp, Warning, TEXT("Player reached the win trigger!"));

	if (WinScreenWidgetClass)
	{
		WinScreenWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WinScreenWidgetClass);
		if (WinScreenWidgetInstance)
		{
			WinScreenWidgetInstance->AddToViewport();

			// Optional: pause the game and show the mouse cursor for a menu-style win screen
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				PC->SetShowMouseCursor(true);
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(WinScreenWidgetInstance->TakeWidget());
				PC->SetInputMode(InputMode);
			}
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}
}

