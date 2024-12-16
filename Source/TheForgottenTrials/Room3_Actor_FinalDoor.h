// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room3_Actor_FinalDoor.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom3_Actor_FinalDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom3_Actor_FinalDoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* doorMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator targetRotation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float rotationSpeed;

	FRotator initialRotation;
	bool rotating;
};
