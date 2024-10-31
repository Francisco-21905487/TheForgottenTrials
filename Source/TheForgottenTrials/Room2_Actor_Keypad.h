// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Room2_Actor_BigPaper.h"
#include "Room2_Actor_Finaldoor.h"
#include "Room2_Actor_Keypad.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API ARoom2_Actor_Keypad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom2_Actor_Keypad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Function to handle interaction
	void Interact();

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

	UFUNCTION(BlueprintCallable)
	bool CheckCode(FString KeypadCode);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> KeypadWidgetClass;

	UPROPERTY(EditAnywhere, Category = "BigPaper")
	ARoom2_Actor_BigPaper* TargetBigPaper;

	// Reference to the door
	UPROPERTY(EditAnywhere, Category = "Door")
	ARoom2_Actor_Finaldoor* TargetFinalDoor;

private:
	// Box component to detect player proximity
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ProximityBox;

	// Static mesh component for the keypad
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KeypadMesh;

	// Function to handle overlap begin
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to handle overlap end
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	UUserWidget* KeypadWidget;

	// Flag to check if player is in range
	bool PlayerInRange;
};
