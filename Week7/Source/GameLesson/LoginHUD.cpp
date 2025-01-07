// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginHUD.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ULoginHUD::SwitchLevel(FName LevelName)
{

    // ��ȡ GameInstance
    UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (GameInstance)
    {
        // ��ʾ���ؽ���
        GameInstance->ShowLoadingScreen();
        LoadingTime = GameInstance->GetLoadingTime();

    }

    // �ӳ� 10 ����л��ؿ�
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, LevelName]()
        {
            // ȷ��Ŀ��ؿ���ͬ
            FString CurrentLevelName = GetWorld()->GetMapName();
            FName CurrentLevel = FName(*CurrentLevelName.RightChop(GetWorld()->StreamingLevelsPrefix.Len()));

            if (CurrentLevel != LevelName)
            {
                // �л���Ŀ��ؿ�
                UGameplayStatics::OpenLevel(this, LevelName);
                // GameInstance->HideLoadingScreen();
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Already in the target level: %s"), *LevelName.ToString());
            }
        }, LoadingTime, false);
}




