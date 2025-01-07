// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Room3_Actor_Symbols.generated.h"

class ARoom3_Actor_SymbolsManager;

UCLASS()
class THEFORGOTTENTRIALS_API ARoom3_Actor_Symbols : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom3_Actor_Symbols();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	bool correctSymbol = false;

	UPROPERTY(Replicated)
	bool resetMovement = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void MoveActorPosition(float DeltaTime, float targetPosition);
	void MoveActorPositionInReverse(float DeltaTime, float targetPosition);

	UPROPERTY(EditAnywhere, Category = "Symbols")
	ARoom3_Actor_SymbolsManager* symbolsManager;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float targetXPosition = 0;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float inicialPosition = 0;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float moveSpeed = 0;

	UPROPERTY(Replicated)
	bool moving = false;
};
