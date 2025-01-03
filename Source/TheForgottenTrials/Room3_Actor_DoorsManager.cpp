// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room3_Actor_DoorsManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ARoom3_Actor_DoorsManager::ARoom3_Actor_DoorsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;
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
	for (int i = 0; i < 4; i++)
	{
		int correctDoorIndex = FMath::RandRange(i * 2, i * 2 + 1);
		MulticastSelectCorrectDoor(correctDoorIndex, i);
	}

	symbolsManager->SetCorrectSymbols();
}

void ARoom3_Actor_DoorsManager::MulticastSelectCorrectDoor_Implementation(int correctDoorIndex, int i)
{
	doors[correctDoorIndex]->correctDoor = true;
	correctDoors[i] = doors[correctDoorIndex];
	arrowsManager->SetArrowRotation(i, correctDoorIndex);
}


void ARoom3_Actor_DoorsManager::ResetRoom3()
{
	// Check if doors array is valid
	if ((sizeof(doors) / sizeof(doors[0])) < 8)
	{
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