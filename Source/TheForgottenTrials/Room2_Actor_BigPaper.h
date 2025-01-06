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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString GetCorrectCode();

	void ResetCode();

private:
	int32 randomNumberArray[4][4];

	void GenerateRandomNumbersAndDisplay();

	UTextRenderComponent* textRender;

	UPROPERTY(EditAnywhere)
	int bigPaperID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
