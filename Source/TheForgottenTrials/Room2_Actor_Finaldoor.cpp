// Fill out your copyright notice in the Description page of Project Settings.


#include "Room2_Actor_Finaldoor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ARoom2_Actor_Finaldoor::ARoom2_Actor_Finaldoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = doorMesh;
	doorMesh->SetIsReplicated(true);

    targetRotation = FRotator(0.0f, 90.0f, 0.0f); // Example: Rotate 90 degrees on the Yaw axis
    rotationSpeed = 2.0f; // Adjust rotation speed as needed
    rotating = false;

	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ARoom2_Actor_Finaldoor::BeginPlay()
{
	Super::BeginPlay();

    initialRotation = GetActorRotation();
	
}

// Called every frame
void ARoom2_Actor_Finaldoor::Tick(float DeltaTime)
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

void ARoom2_Actor_Finaldoor::OpenDoor()
{
	rotating = true;

	Play2DSound();

	// Toggle between opening and closing
	if (GetActorRotation().Equals(initialRotation, 1.0f))
	{
		targetRotation = initialRotation + FRotator(0.0f, 90.0f, 0.0f); // Open door
	}
}

void ARoom2_Actor_Finaldoor::Play2DSound()
{
	if (doorSound)
	{
		UGameplayStatics::PlaySound2D(this, doorSound, 2.0f /*Volume*/, 1.0f /*Pitch*/, 0.8f /*StartTime*/);
	}
}

void ARoom2_Actor_Finaldoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoom2_Actor_Finaldoor, rotating);
}