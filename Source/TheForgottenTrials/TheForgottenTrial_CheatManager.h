// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TheForgottenTrial_CheatManager.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API UTheForgottenTrial_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	//Room 1
	UFUNCTION(Exec)
	void CompleteRoom1();

	//Room 2
	UFUNCTION(Exec)
	void CompleteRoom2();

	//Room 3
	UFUNCTION(Exec)
	void CompleteRoom3();

	/*
	//Room 4
	UFUNCTION(Exec)
	void CompleteRoom4();
	*/
};
