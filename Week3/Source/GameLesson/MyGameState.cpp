// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"

AMyGameState::AMyGameState()
{
    // ����ÿ֡���� Tick
    PrimaryActorTick.bCanEverTick = true;

    // ��ȡ GameMode �е� TimeRemaining ����
    AGameLessonGameMode* GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        // ��ȡ GameMode �е�ʣ��ʱ��
        TimeRemaining = GameMode->GetTimeRemaining();
    }
}

void AMyGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Log, TEXT("Time Left %f"), TimeRemaining);
    // �����Ϸ��δ����������ʣ��ʱ��
    if (TimeRemaining > 0)
    {
        TimeRemaining -= DeltaTime;

        // ��ֹʣ��ʱ���Ϊ����
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
    return 0.0f;  // ����޷���ȡ GameMode������Ĭ��ֵ
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