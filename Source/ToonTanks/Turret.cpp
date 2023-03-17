// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


ATurret::ATurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackDistance = 300;
	IdleRotationRange = 50;
	InitTurretRotation = FRotator(0);
	IdleRotateRight = FRotator(0);
	IdleRotateLeft = FRotator(0);
	isAggred = false;
	isIdle = true;
	rotateRight = true;
	FireRate = 2;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	InitTurretRotation = GetTurret()->GetComponentRotation();
	IdleRotateRight = FRotator(InitTurretRotation.Pitch, InitTurretRotation.Yaw - IdleRotationRange, InitTurretRotation.Roll);
	IdleRotateLeft = FRotator(InitTurretRotation.Pitch, InitTurretRotation.Yaw + IdleRotationRange, InitTurretRotation.Roll);
	SetTurretRotationSpeed(3);
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurret::FireProjectile, FireRate, true);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SwitchStateOfTower();
	RotateTower();
}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ATurret::verifyIfTurretRotationIsEqualTo(FRotator Rotation) {

	if (GetTurret()->GetComponentRotation().Equals(Rotation, 1.f)) {
		return true;
	}
	else {
		return false;
	}
}

void ATurret::FireProjectile() {
	if (isAggred) {
		Super::FireProjectile();
	}
}

void ATurret::SwitchStateOfTower() {
	if (PlayerPawn) {
		if (FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()) <= AttackDistance) {
			isIdle = false;
			isAggred = true;
			SetTurretRotationSpeed(10);
		}
		else {
			isAggred = false;
		}
	}
}

void ATurret::RotateTower() {
	if (isAggred) {

		TurnTurret(PlayerPawn->GetActorLocation());
	}
	else if (!isAggred && !isIdle) {
		TurnTurret(InitTurretRotation);

		if (verifyIfTurretRotationIsEqualTo(InitTurretRotation)) {
			isIdle = true;
			SetTurretRotationSpeed(3);
		}
	}
	else {
		if (rotateRight) {
			TurnTurret(IdleRotateRight);
			if (verifyIfTurretRotationIsEqualTo(IdleRotateRight)) {
				rotateRight = false;
			}
		}
		else {
			TurnTurret(IdleRotateLeft);
			if (verifyIfTurretRotationIsEqualTo(IdleRotateLeft)) {
				rotateRight = true;
			}
		}
	}
}
