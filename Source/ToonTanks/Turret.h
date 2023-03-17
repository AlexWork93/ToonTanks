// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void FireProjectile() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	bool verifyIfTurretRotationIsEqualTo(FRotator Rotation);
	void SwitchStateOfTower();
	void RotateTower();

	APawn* PlayerPawn;
	FRotator InitTurretRotation;
	FRotator IdleRotateRight;
	FRotator IdleRotateLeft;

	float AttackDistance;
	float IdleRotationRange;
	bool rotateRight;
	bool isAggred;
	bool isIdle;

	FTimerHandle FireTimerHandle;
	float FireRate;
};
