// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room1_Actor_PressurePlate.generated.h"

class ARoom1_Actor_MazeDoors;

UCLASS()
class THEFORGOTTENTRIALS_API ARoom1_Actor_PressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom1_Actor_PressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
    // Trigger Volume to detect overlap
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* TriggerBox;

    // Mesh for the pressure plate
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* PressurePlateMesh;

    // Reference to the door
    UPROPERTY(EditAnywhere, Category = "Door")
    ARoom1_Actor_MazeDoors* TargetDoor;

    // The target position to lower the plate to
    UPROPERTY(EditAnywhere, Category = "Plate Movement")
    float LoweredHeight = 10.0f;

    // The speed at which the plate lowers/raises
    UPROPERTY(EditAnywhere, Category = "Plate Movement")
    float LoweringSpeed = 50.0f;

    // Function to handle stepping on the pressure plate
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    // Store the initial and target positions
    FVector InitialLocation;
    FVector TargetLocation;

    // Flag to track if the plate should be lowering or raising
    bool bIsLowering = false;
    bool bIsRaising = false;
};
