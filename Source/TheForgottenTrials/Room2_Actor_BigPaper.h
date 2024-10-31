// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Room2_Actor_BigPaper.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom2_Actor_BigPaper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom2_Actor_BigPaper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	FString GetCorrectCode();

	void ResetCode();

protected:
	int32 RandomNumberArray[4][4];

	void GenerateRandomNumbersAndDisplay();

	UTextRenderComponent* TextRender;

private:
	UPROPERTY(EditAnywhere)
	int BigPaperID;
};
