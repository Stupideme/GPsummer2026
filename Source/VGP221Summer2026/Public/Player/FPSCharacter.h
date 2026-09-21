// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile/FPSProjectile.h"
#include "FPSCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);

UCLASS()
class VGP221SUMMER2026_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FPSMeshComponent;

	UPROPERTY(EditAnywhere)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void OnHurtPlayer(float DamageAmount);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FOnPlayerDied OnPlayerDied;

private:
	float Health = 100.0f;
	float MaxHealth = 100.0f;
};
