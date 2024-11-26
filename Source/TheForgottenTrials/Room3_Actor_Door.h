// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Room3_Actor_Symbols.h"
#include "Room3_Actor_Door.generated.h"

class ARoom3_Actor_DoorsManager;

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

		UPROPERTY(EditAnywhere, Category = "Symbol")
		ARoom3_Actor_Symbols* symbolActor;

		bool correctDoor = false;

		void CloseDoor();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		void MoveDoor(float DeltaTime, FRotator targetPosition);

		void OpenDoor();

		UPROPERTY(EditAnywhere, Category = "Doors")
		ARoom3_Actor_DoorsManager* doorsManager;

		UPROPERTY(EditAnywhere, Category = "Movement")
		FRotator targetRotation;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float rotationSpeed;

		FRotator initialRotation;

		bool opening;
};
