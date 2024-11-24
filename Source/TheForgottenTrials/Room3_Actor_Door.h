// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Room3_Actor_Door.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom3_Actor_Door : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ARoom3_Actor_Door();
		
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		virtual void Interact() override;

		bool correctDoor = false;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		void OpenDoor();

		UPROPERTY(EditAnywhere, Category = "Movement")
		float targetZPosition;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float moveSpeed;

		bool opening;
};
