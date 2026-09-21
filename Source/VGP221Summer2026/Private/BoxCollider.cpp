// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxCollider.h"

// Sets default values
ABoxCollider::ABoxCollider()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box component and make it the root
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	// Set the box extent (half-size in each direction)
	BoxCollision->SetBoxExtent(BoxExtent);

	// Enable both physical collision AND overlap queries
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Set it to physically block everything by default...
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	// ...but you can still generate overlap events on top of blocking,
	// e.g. if you want it to overlap Pawns specifically while blocking everything else:
	// BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Make sure overlap events are actually generated (blocking components don't generate them by default in some setups)
	BoxCollision->SetGenerateOverlapEvents(true);

	// Enable physics simulation notifications for hit events (needed for OnComponentHit to fire)
	BoxCollision->SetNotifyRigidBodyCollision(true);

	// Bind overlap events
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoxCollider::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABoxCollider::OnOverlapEnd);

	// Bind hit event (for blocking collisions)
	BoxCollision->OnComponentHit.AddDynamic(this, &ABoxCollider::OnHit);
}

// Called when the game starts or when spawned
void ABoxCollider::BeginPlay()
{
	Super::BeginPlay();

	// Apply the editable extent in case it was changed in the Editor
	BoxCollision->SetBoxExtent(BoxExtent);
}

// Called every frame
void ABoxCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxCollider::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap began with: %s"), *OtherActor->GetName());
	}
}

void ABoxCollider::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap ended with: %s"), *OtherActor->GetName());
	}
}

void ABoxCollider::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetName());
	}
}