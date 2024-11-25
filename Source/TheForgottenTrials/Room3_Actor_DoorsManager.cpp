// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room3_Actor_DoorsManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ARoom3_Actor_DoorsManager::ARoom3_Actor_DoorsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom3_Actor_DoorsManager::BeginPlay()
{
	Super::BeginPlay();

	SelectCorrectDoor();
}

// Called every frame
void ARoom3_Actor_DoorsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoom3_Actor_DoorsManager::SelectCorrectDoor()
{
	// Choose a random door to be the correct one
	// First sequence of doors
	int correctDoorIndex = FMath::RandRange(0, 1);
	doors[correctDoorIndex]->correctDoor = true;
	correctDoors[0] = doors[correctDoorIndex];
	arrowsManager->SetArrowRotation(0, correctDoorIndex);

	// Second sequence of doors
	correctDoorIndex = FMath::RandRange(2, 3);
	doors[correctDoorIndex]->correctDoor = true;
	correctDoors[1] = doors[correctDoorIndex];
	arrowsManager->SetArrowRotation(1, correctDoorIndex);

	// Third sequence of doors
	correctDoorIndex = FMath::RandRange(4, 5);
	doors[correctDoorIndex]->correctDoor = true;
	correctDoors[2] = doors[correctDoorIndex];
	arrowsManager->SetArrowRotation(2, correctDoorIndex);

	// Fourth sequence of doors
	correctDoorIndex = FMath::RandRange(6, 7);
	doors[correctDoorIndex]->correctDoor = true;
	correctDoors[3] = doors[correctDoorIndex];
	arrowsManager->SetArrowRotation(3, correctDoorIndex);

	symbolsManager->SetCorrectSymbols();
}

void ARoom3_Actor_DoorsManager::ResetRoom3()
{
	// Check if doors array is valid
	if ((sizeof(doors) / sizeof(doors[0])) < 8)
	{
		UE_LOG(LogTemp, Error, TEXT("Doors array does not have enough elements."));
		return;
	}

	// Reset the correct doors
	for (int i = 0; i < 8; i++)
	{
		if (doors[i])
		{
			doors[i]->correctDoor = false;
			doors[i]->CloseDoor();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Door %d is nullptr."), i);
		}
	}

	// Reset the correctDoors array
	for (int i = 0; i < 4; i++)
	{
		correctDoors[i] = nullptr;
	}

	// Select again the correct doors
	SelectCorrectDoor();

	//Reset the player to the beginning of the room3
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController && playerController->GetPawn())
	{
		playerController->GetPawn()->SetActorLocation(waypointStartRoom3->GetActorLocation());
	}
}