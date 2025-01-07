// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportsManager.h"

// Sets default values
ATeleportsManager::ATeleportsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleportsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

