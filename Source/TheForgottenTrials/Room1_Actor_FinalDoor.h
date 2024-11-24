// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Room1_Actor_FinalDoor.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom1_Actor_FinalDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom1_Actor_FinalDoor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OpenDoor();

	void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* doorMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DoorTriggerBox;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator targetRotation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float rotationSpeed;

	FRotator initialRotation;
	bool rotating;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
