// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class ULoadingHUD;
class ULoginHUD;

/**
 * 
 */
UCLASS()
class GAMELESSON_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UMyGameInstance();

    // 控制加载时间
    UPROPERTY(BlueprintReadWrite, Category = "Loading")
    float LoadingTime;

    UFUNCTION(BlueprintCallable, Category = "Loading")
    float GetLoadingTime();

    // 保存 TextBox 文本的变量
    UPROPERTY(BlueprintReadWrite, Category = "PlayerName")
    FString PlayerName;

    // 设置文本
    UFUNCTION(BlueprintCallable, Category = "PlayerName")
    void SetPlayerName(const FString& NewText);

    // 获取文本
    UFUNCTION(BlueprintCallable, Category = "PlayerName")
    FString GetPlayerName() const;
	
    // 加载界面
    UPROPERTY()
    ULoadingHUD* HUD_Loading;

    // 登录界面
    UPROPERTY()
    ULoginHUD* HUD_Login;

    // 显示加载界面
    void ShowLoadingScreen();

    // 隐藏加载界面
    void HideLoadingScreen();
	
    

};
