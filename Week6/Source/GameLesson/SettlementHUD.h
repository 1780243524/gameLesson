// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettlementHUD.generated.h"

class UVerticalBox;

/**
 * 
 */
UCLASS()
class GAMELESSON_API USettlementHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Meta = (BindWidget))
	UVerticalBox* VerticalBoxScores;
	
	// 添加分数
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore();

private:

	// 动态添加 TextBlock 到 VerticalBoxScores
	void AddPlayerScoreToUI(FString PlayerName, int32 Score);
};
