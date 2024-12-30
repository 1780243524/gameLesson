// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginHUD.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ULoginHUD::SwitchLevel(FName LevelName)
{

    // 获取 GameInstance
    UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (GameInstance)
    {
        // 显示加载界面
        GameInstance->ShowLoadingScreen();
        LoadingTime = GameInstance->GetLoadingTime();

    }

    // 延迟 10 秒后切换关卡
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, LevelName]()
        {
            // 确保目标关卡不同
            FString CurrentLevelName = GetWorld()->GetMapName();
            FName CurrentLevel = FName(*CurrentLevelName.RightChop(GetWorld()->StreamingLevelsPrefix.Len()));

            if (CurrentLevel != LevelName)
            {
                // 切换到目标关卡
                UGameplayStatics::OpenLevel(this, LevelName);
                // GameInstance->HideLoadingScreen();
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Already in the target level: %s"), *LevelName.ToString());
            }
        }, LoadingTime, false);
}




