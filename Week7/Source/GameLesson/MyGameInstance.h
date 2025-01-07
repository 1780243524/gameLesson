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

    // ���Ƽ���ʱ��
    UPROPERTY(BlueprintReadWrite, Category = "Loading")
    float LoadingTime;

    UFUNCTION(BlueprintCallable, Category = "Loading")
    float GetLoadingTime();

    // ���� TextBox �ı��ı���
    UPROPERTY(BlueprintReadWrite, Category = "PlayerName")
    FString PlayerName;

    // �����ı�
    UFUNCTION(BlueprintCallable, Category = "PlayerName")
    void SetPlayerName(const FString& NewText);

    // ��ȡ�ı�
    UFUNCTION(BlueprintCallable, Category = "PlayerName")
    FString GetPlayerName() const;
	
    // ���ؽ���
    UPROPERTY()
    ULoadingHUD* HUD_Loading;

    // ��¼����
    UPROPERTY()
    ULoginHUD* HUD_Login;

    // ��ʾ���ؽ���
    void ShowLoadingScreen();

    // ���ؼ��ؽ���
    void HideLoadingScreen();
	
    

};
