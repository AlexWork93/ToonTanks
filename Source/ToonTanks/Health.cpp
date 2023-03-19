// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "Tank.h"


// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	MaxHealth = 100.f;
	Health = MaxHealth;
	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::DamageTaken);
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser) {

	Health -= Damage;
	if (Health < 0)
	{
		Health = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s health = %f"), *GetOwner()->GetName(), Health);
	if (Health == 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("owner %s"), *(GetOwner()->GetClass().toCompactString()));
		//UE_LOG(LogTemp, Warning, TEXT("tank %s"), *(ATank::StaticClass().toCompactString()));


		if (GetOwner()->GetClass() == ATank::StaticClass())
		{
			GetOwner()->SetActorHiddenInGame(true);
		}
		else {
			GetOwner()->Destroy();
		}
	}
}

