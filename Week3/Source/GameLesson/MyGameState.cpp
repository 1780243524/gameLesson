// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"

AMyGameState::AMyGameState()
{
    // 启用每帧调用 Tick
    PrimaryActorTick.bCanEverTick = true;

    // 获取 GameMode 中的 TimeRemaining 变量
    AGameLessonGameMode* GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        // 获取 GameMode 中的剩余时间
        TimeRemaining = GameMode->GetTimeRemaining();
    }
}

void AMyGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Log, TEXT("Time Left %f"), TimeRemaining);
    // 如果游戏尚未结束，减少剩余时间
    if (TimeRemaining > 0)
    {
        TimeRemaining -= DeltaTime;

        // 防止剩余时间变为负数
        if (TimeRemaining < 0)
        {
            TimeRemaining = 0;
        }
    }
}

float AMyGameState::GetTimeRemaining() const
{
    //UE_LOG(LogTemp, Log, TEXT("Try Get Time"));
    AGameLessonGameMode* GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        // UE_LOG(LogTemp, Log, TEXT("Get Time %f"), TimeRemaining);
        return TimeRemaining;
    }
    return 0.0f;  // 如果无法获取 GameMode，返回默认值
}

void AMyGameState::UpdatePlayerScores(int32 PlayerId, int32 PlayerScore) {
    if (PlayerScores.Contains(PlayerId)) {
        PlayerScores[PlayerId] = PlayerScore;
    }
    else {
        PlayerScores.Add(PlayerId, PlayerScore);
    }
}

TMap<int32, int32> AMyGameState::GetPlayerScores() const {
    return PlayerScores;
}