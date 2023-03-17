// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TurnTurret(FVector ToTargetVector);
	void TurnTurret(FRotator ToTargetRotator);
	void SetTurretRotationSpeed (float speed);
	virtual void FireProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UStaticMeshComponent* GetTurret() { return TurretMesh; }
private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* ColliderBox;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* ProjectileSpawnPoint;

	float TurretRoTationSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
};
