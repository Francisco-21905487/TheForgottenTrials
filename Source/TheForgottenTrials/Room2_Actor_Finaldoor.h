// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room2_Actor_Finaldoor.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom2_Actor_Finaldoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom2_Actor_Finaldoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OpenDoor();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* doorMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float targetZPosition;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float moveSpeed;

	bool opening;
	FVector initialPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
