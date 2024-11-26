// Fill out your copyright notice in the Description page of Project Settings.


#include "Room3_Actor_Door.h"
#include "Room3_Actor_DoorsManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoom3_Actor_Door::ARoom3_Actor_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom3_Actor_Door::BeginPlay()
{
	Super::BeginPlay();

	initialRotation = GetActorRotation();
	
}

// Called every frame
void ARoom3_Actor_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (opening)
	{
		MoveDoor(DeltaTime, targetRotation);
	}

}

void ARoom3_Actor_Door::MoveDoor(float DeltaTime, FRotator targetPosition)
{
	FVector currentLocation = GetActorLocation();

	FRotator currentRotation = GetActorRotation();
	FRotator newRotation = FMath::RInterpTo(currentRotation, targetPosition, DeltaTime, rotationSpeed);
	SetActorRotation(newRotation);

	// Stop rotating when the target rotation is reached
	if (currentRotation.Equals(targetPosition, 1.0f)) // Tolerance of 1 degree
	{
		opening = false;
	}
}

void ARoom3_Actor_Door::OpenDoor()
{
	opening = true;

	// Toggle between opening and closing
	if (GetActorRotation().Equals(initialRotation, 1.0f))
	{
		targetRotation = initialRotation + FRotator(0.0f, -90.0f, 0.0f); // Open door
	}
}

void ARoom3_Actor_Door::CloseDoor()
{
	opening = false;

	SetActorRotation(initialRotation);
}

void ARoom3_Actor_Door::Interact()
{
	if (correctDoor)
	{
		OpenDoor();
	}
	else 
	{
		// Reset the player to the start of the level and reset the correct doors
		doorsManager->ResetRoom3();

		//If we want to add some user feedback put it here
	}
}
