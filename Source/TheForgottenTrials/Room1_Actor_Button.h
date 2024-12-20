// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Room1_Actor_FinalDoor.h"
#include "Interactable.h"
#include "Room1_Actor_Button.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom1_Actor_Button : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom1_Actor_Button();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

private:
	// Box component to detect player proximity
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* proximityBox;

	// Static mesh component for the keypad
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* buttonMesh;

	// Reference to the door
	UPROPERTY(EditAnywhere, Category = "Door")
	ARoom1_Actor_FinalDoor* targetFinalDoor;

	// Function to handle overlap begin
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to handle overlap end
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Flag to check if player is in range
	bool playerInRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
