// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
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

	UFUNCTION(Server, Reliable)
	void Server_Play2DSound(APlayerController* InteractingController);
	
	APlayerController * interactController;

	bool correctSymbol = false;

	UPROPERTY(Replicated)
	bool resetMovement = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_MoveActorPosition(float DeltaTime, float targetPosition);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_MoveActorPositionInReverse(float DeltaTime, float targetPosition);
	
	// Function to handle overlap begin
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Symbols")
	ARoom3_Actor_SymbolsManager* symbolsManager;

	// Box component to detect player proximity
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* proximityBox;

	// Sound asset to play
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* buttonSound;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float targetXPosition = 0;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float inicialPosition = 0;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float moveSpeed = 0;

	UPROPERTY(Replicated)
	bool moving = false;
};
