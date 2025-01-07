// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rooms_Actor_CheatManager.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARooms_Actor_CheatManager : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ARooms_Actor_CheatManager();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		//Room 1
		void CompleteRoom1();

		//Room 2
		void CompleteRoom2();

		//Room 3
		void CompleteRoom3();

		void ShowCodeRoom2();

		//Teleport functions
		void TeleportToWaypoint(int id);

		void TeleportToNextWaypoint();

		void TeleportToPreviousWaypoint();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		int32 currentWaypoint;
};
