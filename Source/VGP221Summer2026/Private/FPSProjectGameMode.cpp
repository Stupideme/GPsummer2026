// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProjectGameMode.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPSCharacter.h"

void AFPSProjectGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// 1. Print to screen
	// Display a debug message for five seconds.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode! This is with editor open"));

	// 2. Print to log
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	// 3. Printing values using specifiers
	int TestNumber = 5;
	bool TestBool = true; //  0 or 1
	UE_LOG(LogTemp, Warning, TEXT("Test Number: %i"), TestNumber);
	UE_LOG(LogTemp, Warning, TEXT("Test Bool: %i"), TestBool);
	UE_LOG(LogTemp, Warning, TEXT("Test Bool String: %s"), TestBool ? TEXT("true") : TEXT("false"));

	// 4. Pointers & References
	int* TestNumberPtr = &TestNumber;

	UE_LOG(LogTemp, Warning, TEXT("TestNumber Ref: %p"), &TestNumber);
	UE_LOG(LogTemp, Warning, TEXT("TestNumber Ptr: %p"), TestNumberPtr);

	UE_LOG(LogTemp, Warning, TEXT("This will be large number: %i"), TestNumberPtr);

	UE_LOG(LogTemp, Warning, TEXT("TestNumber: %i"), *TestNumberPtr); // Dereferencing the pointer to get the value it points to

	// 5. Giving a nickname to a variable
	int& NicknameForTestNumber = TestNumber;
	NicknameForTestNumber = 10;
	UE_LOG(LogTemp, Warning, TEXT("New Test Number: %i"), TestNumber);

	// 6. Printing a string
	FString TestString = TEXT("Hello, Unreal!");
	UE_LOG(LogTemp, Warning, TEXT("Test String: %s"), *TestString);

	//7. Causing a crash with a pointer
	int* CrashPointer = nullptr;
	//UE_LOG(LogTemp, Warning, TEXT("This will cause a crash: %i"), *CrashPointer);

	// 8. Using structured logging
	UE_LOGFMT(LogTemp, Warning, "Structured Logging: Test Number: {0}, Test Bool: {1}, Test String: {2}", TestNumber, TestBool, *TestString);

	// Get player and bind a function to when player died
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->OnPlayerDied.AddDynamic(this, &AFPSProjectGameMode::GoToGameOver);
}

void AFPSProjectGameMode::GoToGameOver()
{
	//UGameplayStatics::OpenLevel(this, FName("GameMap"));
	UE_LOG(LogTemp, Warning, TEXT("Going to gameover map"));
}
