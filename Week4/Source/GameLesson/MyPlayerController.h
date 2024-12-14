// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMELESSON_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	// 是否结算
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settle")
	bool bIsSettled;

	// UFUNCTION(Client, Reliable)
	// TArray <FPlayerScore> Client_GetPlayerScores(const TArray<FPlayerScore>& PlayerScores);

protected:
	virtual void BeginPlay() override;

private:
	// 自定义的输入或控制逻辑

	
};
