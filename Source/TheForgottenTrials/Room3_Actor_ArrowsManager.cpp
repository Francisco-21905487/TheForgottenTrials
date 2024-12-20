// Fill out your copyright notice in the Description page of Project Settings.


#include "Room3_Actor_ArrowsManager.h"

// Sets default values
ARoom3_Actor_ArrowsManager::ARoom3_Actor_ArrowsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom3_Actor_ArrowsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom3_Actor_ArrowsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom3_Actor_ArrowsManager::SetArrowRotation(int arrowIndex, int position)
{
	if (position == 1 || position == 3 || position == 5 || position == 7)
	{
		arrows[arrowIndex]->SetActorRotation(FRotator(-90, 0, 0));
	}
	else
	{
		arrows[arrowIndex]->SetActorRotation(FRotator(90, 0, 0));
	}
}