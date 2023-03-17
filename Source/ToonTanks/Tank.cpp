// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	MovementSpeed = 200;
	TurnSpeed = 100;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerController)
	{
		FHitResult hitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		TurnTurret(hitResult.ImpactPoint);
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 20, 10, FColor::Red);
	}
	FRotator SpringArmRot = SpringArm->GetComponentRotation();
	SpringArm->SetWorldRotation(FRotator(-35 , GetActorRotation().Yaw, 0));

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),EInputEvent::IE_Pressed, this, &ATank::FireProjectile);

	
}

void ATank::Move(float Value) {	
	AddActorLocalOffset(FVector(Value * UGameplayStatics::GetWorldDeltaSeconds(this) * MovementSpeed, 0, 0));
}
void ATank::Turn(float Value) {
	AddActorLocalRotation(FRotator(0, Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed, 0));
}