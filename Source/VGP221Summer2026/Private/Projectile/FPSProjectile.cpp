// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnWhateverWeWantToNameThis);
	RootComponent = CollisionComponent;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

	// 1. Get assets from unreal engine
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));

	// 2. Get assets we imported
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Meshes/Common/Sphere.Sphere"));
	if(ProjectileMeshAsset.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object);
	}

	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	// 3. Setting up material using only c++
	static ConstructorHelpers::FObjectFinder<UMaterial> ProjectileMaterialAsset(TEXT("/Game/Materials/M_Projectile.M_Projectile"));
	if(ProjectileMaterialAsset.Succeeded())
	{
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialAsset.Object);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = BulletSpeed;
	ProjectileMovementComponent->MaxSpeed = BulletSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // No gravity

	InitialLifeSpan = 3.0f; // Destroy after 3 seconds. Unity Destroy(3.0f);
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	// 1. FVector ShootDirection: Pass by value, least efficient. Making a copy of the vector
	// 2. FVector* ShootDirection: Pass by pointer, more efficient. Can be null, need to check for null. 
	// 3. FVector& ShootDirection: Pass by reference, most efficient. No dereferencing, no null check needed.
	// 4. const FVector& ShootDirection: Pass by const reference, most efficient. Cannot modify the original vector.

	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnWhateverWeWantToNameThis(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor);
	if(Enemy)
	{
		Enemy->OnEnemyTakeDamage(100.0f);
		Destroy();
		return;
	}

	// If physics, add impulse then destroy projectile
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics()) {
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());
}


