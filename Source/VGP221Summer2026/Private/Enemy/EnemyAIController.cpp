// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePlayer);
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(StartingBehaviorTree);
}

void AEnemyAIController::OnSeePlayer(APawn* PlayerPawn)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(PlayerPawn);
	if (!PlayerCharacter) return;

	SetCanSeePlayer(true, PlayerCharacter);

	RunRetriggerableCanSeePlayer();
}

void AEnemyAIController::SetCanSeePlayer(bool bCanSee, UObject* PlayerObject)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(TEXT("CanSeePlayer"), bCanSee);
		BlackboardComp->SetValueAsObject(TEXT("PlayerTarget"), PlayerObject);
	}
}

void AEnemyAIController::RunRetriggerableCanSeePlayer()
{
	GetWorldTimerManager().ClearTimer(CanSeePlayerTimerHandle);
	CanSeePlayerTimerDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, nullptr);
	GetWorldTimerManager().SetTimer(CanSeePlayerTimerHandle, CanSeePlayerTimerDelegate, PawnSensing->SensingInterval * 2.0, false);
}