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
	
}

// Called every frame
void ARoom3_Actor_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (opening)
	{
		MoveDoor(DeltaTime, targetZPosition);
	}

}

void ARoom3_Actor_Door::MoveDoor(float DeltaTime, float targetPosition)
{
	FVector currentLocation = GetActorLocation();

	// Smoothly move the door down towards the target Z position
	currentLocation.Z = FMath::FInterpTo(currentLocation.Z, targetPosition, DeltaTime, moveSpeed);
	SetActorLocation(currentLocation);

	// Stop opening when we reach the target position
	if (FMath::IsNearlyEqual(currentLocation.Z, targetPosition, 1.0f))
	{
		opening = false;
	}
}

void ARoom3_Actor_Door::OpenDoor()
{
	opening = true;
}

void ARoom3_Actor_Door::CloseDoor()
{
	opening = false;

	FVector currentLocation = GetActorLocation();
	currentLocation.Z = initialZPosition;
	SetActorLocation(currentLocation);
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
