// Fill out your copyright notice in the Description page of Project Settings.


#include "Room3_Actor_Symbols.h"
#include "Room3_Actor_SymbolsManager.h"

// Sets default values
ARoom3_Actor_Symbols::ARoom3_Actor_Symbols()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom3_Actor_Symbols::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom3_Actor_Symbols::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (moving)
	{
		MoveActorPosition(DeltaTime, targetXPosition);
	}

	if (resetMovement) 
	{
		MoveActorPositionInReverse(DeltaTime, inicialPosition);
	}
}

void ARoom3_Actor_Symbols::MoveActorPosition(float DeltaTime, float targetPosition)
{
	FVector currentLocation = GetActorLocation();

	// Smoothly move the door down towards the target X position
	currentLocation.X = FMath::FInterpTo(currentLocation.X, targetPosition, DeltaTime, moveSpeed);
	SetActorLocation(currentLocation);

	// Stop opening when we reach the target position
	if (FMath::IsNearlyEqual(currentLocation.X, targetPosition, 1.0f))
	{
		symbolsManager->CheckSequenceOfSymbols(this);
		moving = false;
	}
}

void ARoom3_Actor_Symbols::MoveActorPositionInReverse(float DeltaTime, float targetPosition)
{
	FVector currentLocation = GetActorLocation();

	// Smoothly move the door down towards the target X position
	currentLocation.X = FMath::FInterpTo(currentLocation.X, targetPosition, DeltaTime, moveSpeed);
	SetActorLocation(currentLocation);

	// Stop opening when we reach the target position
	if (FMath::IsNearlyEqual(currentLocation.X, targetPosition, 1.0f))
	{
		resetMovement = false;
	}
}

void ARoom3_Actor_Symbols::Interact()
{
	// move the symbol
	moving = true;
	
	//symbolsManager->CheckSequenceOfSymbols(this);
}