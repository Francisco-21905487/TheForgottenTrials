// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room3_Actor_DoorsManager.h"

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
	arrowsManager->SetArrowRotation(0, correctDoorIndex);

	// Second sequence of doors
	correctDoorIndex = FMath::RandRange(2, 3);
	doors[correctDoorIndex]->correctDoor = true;
	arrowsManager->SetArrowRotation(1, correctDoorIndex);

	// Third sequence of doors
	correctDoorIndex = FMath::RandRange(4, 5);
	doors[correctDoorIndex]->correctDoor = true;
	arrowsManager->SetArrowRotation(2, correctDoorIndex);

	// Fourth sequence of doors
	correctDoorIndex = FMath::RandRange(6, 7);
	doors[correctDoorIndex]->correctDoor = true;
	arrowsManager->SetArrowRotation(3, correctDoorIndex);
}