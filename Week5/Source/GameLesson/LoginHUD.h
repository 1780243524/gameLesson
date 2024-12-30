// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMELESSON_API ULoginHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 切换关卡函数
	UFUNCTION(BlueprintCallable, Category = "Level")
	void SwitchLevel(FName LevelName);
	
	// 控制加载时间
	UPROPERTY(BlueprintReadWrite, Category = "Loading")
	float LoadingTime;
};
