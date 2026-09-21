// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WinTrigger.generated.h"

UCLASS()
class YOURPROJECT_API AWinTrigger : public AActor
{
	GENERATED_BODY()

public:
	AWinTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FVector BoxExtent = FVector(100.0f, 100.0f, 100.0f);

	// Widget class for the win screen, set in the Editor (Blueprint widget)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> WinScreenWidgetClass;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

private:
	UPROPERTY()
	UUserWidget* WinScreenWidgetInstance;

	bool bHasTriggered = false;
};