// Fill out your copyright notice in the Description page of Project Settings.


#include "Room3_Actor_FinalDoor.h"

// Sets default values
ARoom3_Actor_FinalDoor::ARoom3_Actor_FinalDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = doorMesh;

	rotationSpeed = 2.0f; // Adjust rotation speed as needed
	rotating = false;
}

// Called when the game starts or when spawned
void ARoom3_Actor_FinalDoor::BeginPlay()
{
	Super::BeginPlay();

	initialRotation = GetActorRotation();
	
}

// Called every frame
void ARoom3_Actor_FinalDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();

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

void ARoom3_Actor_FinalDoor::OpenDoor()
{
	rotating = true;

	// Toggle between opening and closing
	if (GetActorRotation().Equals(initialRotation, 1.0f))
	{
		targetRotation = initialRotation + FRotator(0.0f, -90.0f, 0.0f); // Open door
	}
}