// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BoxCollider.generated.h"

UCLASS()
class YOURPROJECT_API ABoxCollider : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoxCollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The box collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	// Editable box extent (half-size) so you can tweak per-instance in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FVector BoxExtent = FVector(50.0f, 50.0f, 50.0f);

	// Called when something overlaps the box
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	// Called when something stops overlapping the box
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when the box physically hits something (blocking collision)
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};