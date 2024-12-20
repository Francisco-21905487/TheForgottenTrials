// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinTrigger.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API AWinTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinTrigger();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Box component for collision detection
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* TriggerBox;

	// Handle overlap events
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Name of the win menu level
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	FName winmenu;
};
