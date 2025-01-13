// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Room3_Actor_Door.h"
#include "Room3_Actor_ArrowsManager.h"
#include "Room3_Actor_SymbolsManager.h"
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

		ARoom3_Actor_Door* correctDoors[4];

		void ResetRoom3();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		void SelectCorrectDoor();

		UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION(NetMulticast, Reliable)
		void MulticastSelectCorrectDoor(int correctDoorIndex, int i);

		UFUNCTION(Server, Reliable)
		void ServerResetRoom(APlayerController* InteractingController);

		// Box component to detect player proximity
		UPROPERTY(VisibleAnywhere)
		UBoxComponent* proximityBox;

		UPROPERTY(EditAnywhere, Category = "Symbols")
		ARoom3_Actor_SymbolsManager* symbolsManager;

		UPROPERTY(EditAnywhere, Category = "Doors")
		ARoom3_Actor_Door* doors[8];

		UPROPERTY(EditAnywhere, Category = "Arrows")
		ARoom3_Actor_ArrowsManager* arrowsManager;

		UPROPERTY(EditAnywhere)
		AActor* waypointStartRoom3;

		APlayerController* interactController;
};