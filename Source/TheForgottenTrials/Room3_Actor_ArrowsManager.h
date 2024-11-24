// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room3_Actor_ArrowsManager.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom3_Actor_ArrowsManager : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ARoom3_Actor_ArrowsManager();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		void SetArrowRotation(int arrowIndex, int position);

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, Category = "Arrows")
		AActor* arrows[4];
};
