// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_MazeDoors.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoom1_Actor_MazeDoors::ARoom1_Actor_MazeDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = doorMesh;

    targetRotation = FRotator(0.0f, 90.0f, 0.0f); // Example: Rotate 90 degrees on the Yaw axis
    rotationSpeed = 2.0f; // Adjust rotation speed as needed
    rotating = false;

}

// Called when the game starts or when spawned
void ARoom1_Actor_MazeDoors::BeginPlay()
{
	Super::BeginPlay();

    initialRotation = GetActorRotation();
}

// Called every frame
void ARoom1_Actor_MazeDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (rotating)
	{
		FRotator currentRotation = GetActorRotation();
		FRotator newRotation = FMath::RInterpTo(currentRotation, targetRotation, DeltaTime, rotationSpeed);
		SetActorRotation(newRotation);

		// Stop rotating when the target rotation is reached
		if (currentRotation.Equals(targetRotation, 1.0f)) // Tolerance of 1 degree
		{
			rotating = false;
		}
	}
}

void ARoom1_Actor_MazeDoors::OpenDoor()
{
	rotating = true;

	// Toggle between opening and closing
	if (GetActorRotation().Equals(initialRotation, 1.0f))
	{
		targetRotation = initialRotation + FRotator(0.0f, 90.0f, 0.0f); // Open door
	}
}