// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room1_Actor_MazeDoors.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom1_Actor_MazeDoors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom1_Actor_MazeDoors();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OpenDoor();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* doorMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator targetRotation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float rotationSpeed;

	FRotator initialRotation;
	bool rotating;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
