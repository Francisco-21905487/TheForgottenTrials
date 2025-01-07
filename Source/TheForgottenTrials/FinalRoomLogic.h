// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room4_Actor_FinalDoor.h"
#include "FinalRoomLogic.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API AFinalRoomLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinalRoomLogic();

	UFUNCTION(BlueprintCallable, Category = "Voting")
	void RegisterVote(FString Character, FString VoteFor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Outcome determination
	void DetermineOutcome();

	// Voting tally
	FString EthanVote;
	FString IsabelVote;

	UPROPERTY(EditAnywhere, Category = "Doors")
	ARoom4_Actor_FinalDoor* EthanDoor;

	UPROPERTY(EditAnywhere, Category = "Doors")
	ARoom4_Actor_FinalDoor* IsabelDoor;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> loseWidgetClass;

};
