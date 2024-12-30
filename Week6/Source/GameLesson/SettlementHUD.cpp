// Fill out your copyright notice in the Description page of Project Settings.


#include "SettlementHUD.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"  // 需要包含 TextBlock 组件
#include "Components/Widget.h"  // 用于访问添加的 Widget
#include "Net/UnrealNetwork.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "MyGameState.h"

void USettlementHUD::AddScore() {
    // UE_LOG(LogTemp, Log, TEXT("Try AddScore"));
    AMyGameState* MyGameState = GetWorld() != nullptr ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
    int32 PlayerUniqueId = GetWorld()->GetFirstPlayerController()->PlayerState->GetPlayerId();

    if (MyGameState)
    {
        // UE_LOG(LogTemp, Log, TEXT("AddScore"));
        // 获取 PlayerScores 哈希表
        TMap<FString, int32> PlayerScores = MyGameState->GetPlayerScores();

        int32 AllScore = 0;

        // 遍历 PlayerScores 数组并在 HUD 上显示每个玩家的分数
        for (const TPair<FString, int32>& PlayerScore : PlayerScores)
        {
            FString PlayerName = PlayerScore.Key;
            int32 Score = PlayerScore.Value;

            // 生成玩家名称
            // FString PlayerName = FString::Printf(TEXT("Player %d"), PlayerId);

            // 添加玩家分数到 UI
            AddPlayerScoreToUI(PlayerName, Score);

            // 累加总分
            AllScore += Score;
        }
        AddPlayerScoreToUI("All", AllScore);
    }
}

// 动态添加 TextBlock 到 VerticalBoxScores
void USettlementHUD::AddPlayerScoreToUI(FString PlayerName, int32 Score)
{
    if (VerticalBoxScores)
    {
        // 创建一个新的 TextBlock
        UTextBlock* NewTextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());

        // 设置 TextBlock 的文本内容
        FString ScoreText = PlayerName + TEXT(": ") + FString::Printf(TEXT("%d"), Score) + TEXT("\n ");
        NewTextBlock->SetText(FText::FromString(ScoreText));

        // 将 TextBlock 添加到 VerticalBox
        VerticalBoxScores->AddChildToVerticalBox(NewTextBlock);
    }
}




