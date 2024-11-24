// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room3_Actor_Door.h"
#include "Room3_Actor_ArrowsManager.h"
#include "Room3_Actor_DoorsManager.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom3_Actor_DoorsManager : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ARoom3_Actor_DoorsManager();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		void SelectCorrectDoor();

		UPROPERTY(EditAnywhere, Category = "Doors")
		ARoom3_Actor_Door* doors[8];

		UPROPERTY(EditAnywhere, Category = "Arrows")
		ARoom3_Actor_ArrowsManager* arrowsManager;
};
