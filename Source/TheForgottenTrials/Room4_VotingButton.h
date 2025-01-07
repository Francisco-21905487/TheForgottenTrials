// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.h"
#include "FinalRoomLogic.h"
#include "Room4_VotingButton.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom4_VotingButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom4_VotingButton();

	virtual void Tick(float DeltaTime) override;

    virtual void Interact() override;

	// The character this button votes for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voting")
	FString VoteFor;  // Example: "Isabel" or "Ethan"

	// Reference to the Final Room Logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voting")
	class AFinalRoomLogic* FinalRoomLogic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    // Box component to detect player proximity
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* ProximityBox;

    // Static mesh component for the button
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* ButtonMesh;

    // Track if player is in range
    bool bPlayerInRange;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
