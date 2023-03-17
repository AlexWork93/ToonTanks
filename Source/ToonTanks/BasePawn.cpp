// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TurretRoTationSpeed = 10;
	ColliderBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderBox"));
	RootComponent = ColliderBox;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(ColliderBox);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::TurnTurret(FVector ToTargetVector) {
	FRotator ToTargetRotator = FRotator(0, (ToTargetVector - TurretMesh->GetComponentLocation()).Rotation().Yaw, 0);
	TurnTurret(ToTargetRotator);
}

void ABasePawn::TurnTurret(FRotator ToTargetRotator) {
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), ToTargetRotator, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), TurretRoTationSpeed));
}

void ABasePawn::SetTurretRotationSpeed(float speed) {
	TurretRoTationSpeed = speed;
}

void ABasePawn::FireProjectile() {
	DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 20, 12, FColor::Green, false, 0.3);
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	SpawnedProjectile->SetOwner(this);
}
