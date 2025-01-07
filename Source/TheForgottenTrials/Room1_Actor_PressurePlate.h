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

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* triggerBox;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* pressurePlateMesh;

    UPROPERTY(EditAnywhere, Category = "Door")
    ARoom1_Actor_MazeDoors* targetDoor;

    UPROPERTY(EditAnywhere, Category = "Plate Movement")
    float loweredHeight = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Plate Movement")
    float loweringSpeed = 50.0f;

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    FVector initialLocation;
    FVector targetLocation;

    bool lowering = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
