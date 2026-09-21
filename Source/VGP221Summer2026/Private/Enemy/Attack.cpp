// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Attack.h"

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Method 1: Get player character and calling a function
	// AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// PlayerCharacter->OnHurtPlayer(1.0f);

	// Method 2: Using Blackboard to get player target
	// AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("PlayerTarget"));
	// PlayerCharacter->OnHurtPlayer(2.0f);

	// Method 3: Passing variables from the EnemyCharacter or EnemyAIController
	// AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	// AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(EnemyAIController->GetPawn());
	// 
	// float DamageAmt = EnemyCharacter->EnemyDamage;
	// 
	// AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// PlayerCharacter->OnHurtPlayer(DamageAmt);

	// Method 4: Using built in damage system
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UGameplayStatics::ApplyDamage(Character, 20.0f, OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn(), UDamageType::StaticClass());

	return EBTNodeResult::Succeeded;
}
