// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Serialization/StructuredArchive.h"
#include "Room3_Actor_Symbols.h"
#include "Room3_Actor_Door.h"
#include "Room3_Actor_FinalDoor.h"
#include "Room3_Actor_SymbolsManager.generated.h"

class ARoom3_Actor_DoorsManager;

UCLASS()
class THEFORGOTTENTRIALS_API ARoom3_Actor_SymbolsManager : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ARoom3_Actor_SymbolsManager();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		void SetCorrectSymbols();

		void CheckSequenceOfSymbols(ARoom3_Actor_Symbols* interactedSymbol);

		UPROPERTY(EditAnywhere, Category = "Final Door")
		ARoom3_Actor_FinalDoor* finalDoor;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;		

		UPROPERTY(EditAnywhere, Category = "Symbols")
		ARoom3_Actor_Symbols* symbols[8];

		UPROPERTY(EditAnywhere, Category = "Doors")
		ARoom3_Actor_DoorsManager* doorsManager;

		TArray<ARoom3_Actor_Symbols*> correctSymbolSequence;
		int32 currentSequenceIndex = 0;
};