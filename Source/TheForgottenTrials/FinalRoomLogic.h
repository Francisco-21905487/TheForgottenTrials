// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room1_Actor_MazeDoors.h"
#include "FinalRoomLogic.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API AFinalRoomLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinalRoomLogic();

	UFUNCTION(BlueprintCallable, Category = "Voting")
	void RegisterVote(FString VoteFor);

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
	int32 EthanVotes;
	int32 IsabelVotes;

	UPROPERTY(EditAnywhere, Category = "Doors")
	ARoom1_Actor_MazeDoors* EthanDoor;

	UPROPERTY(EditAnywhere, Category = "Doors")
	ARoom1_Actor_MazeDoors* IsabelDoor;

};
