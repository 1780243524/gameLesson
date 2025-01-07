// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "LoadingHUD.h"
#include "LoginHUD.h"

UMyGameInstance::UMyGameInstance()
{
    PlayerName = "Defalut";
    LoadingTime = 5.0f;
}

void UMyGameInstance::SetPlayerName(const FString& NewText)
{
    PlayerName = NewText;
}

FString UMyGameInstance::GetPlayerName() const
{
    return PlayerName;
}

float UMyGameInstance::GetLoadingTime()
{
    return LoadingTime;
}

void UMyGameInstance::ShowLoadingScreen()
{
    FString WidgetClassLoadPath = FString(TEXT("/Game/BluePrint/HUD_Loading.HUD_Loading_C"));
    UClass* TmpWidget = LoadClass<UUserWidget>(NULL, *WidgetClassLoadPath);
    if (TmpWidget)
    {
        // UE_LOG(LogTemp, Log, TEXT("ShowLoadingScreen TmpWidget"))
        HUD_Loading = CreateWidget<ULoadingHUD>(GetWorld(), TmpWidget);
        if (HUD_Loading)
        {
            // UE_LOG(LogTemp, Log, TEXT("ShowLoadingScreen HUD_Loading"));
            HUD_Loading->AddToViewport();
        }
    }
    WidgetClassLoadPath = FString(TEXT("/Game/BluePrint/HUD_Login.HUD_Login_C"));
    TmpWidget = LoadClass<UUserWidget>(NULL, *WidgetClassLoadPath);
    if (TmpWidget)
    {
        // UE_LOG(LogTemp, Log, TEXT("ShowLoadingScreen TmpWidget"))
        HUD_Login = CreateWidget<ULoginHUD>(GetWorld(), TmpWidget);
        if (HUD_Login)
        {
            // UE_LOG(LogTemp, Log, TEXT("ShowLoadingScreen HUD_Loading"));
            HUD_Login->RemoveFromViewport();
        }
    }
}

void UMyGameInstance::HideLoadingScreen()
{
    if (HUD_Loading)
    {
        HUD_Loading->RemoveFromViewport();
        HUD_Loading = nullptr;
    }
}


