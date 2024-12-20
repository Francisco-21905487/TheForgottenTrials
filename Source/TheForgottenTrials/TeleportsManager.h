// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportsManager.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ATeleportsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportsManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Teleports")
	AActor* teleports[8];

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
