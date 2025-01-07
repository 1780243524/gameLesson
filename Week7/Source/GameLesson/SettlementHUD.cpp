// Fill out your copyright notice in the Description page of Project Settings.


#include "SettlementHUD.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"  // ��Ҫ���� TextBlock ���
#include "Components/Widget.h"  // ���ڷ�����ӵ� Widget
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
        // ��ȡ PlayerScores ��ϣ��
        TMap<FString, int32> PlayerScores = MyGameState->GetPlayerScores();

        int32 AllScore = 0;

        // ���� PlayerScores ���鲢�� HUD ����ʾÿ����ҵķ���
        for (const TPair<FString, int32>& PlayerScore : PlayerScores)
        {
            FString PlayerName = PlayerScore.Key;
            int32 Score = PlayerScore.Value;

            // �����������
            // FString PlayerName = FString::Printf(TEXT("Player %d"), PlayerId);

            // �����ҷ����� UI
            AddPlayerScoreToUI(PlayerName, Score);

            // �ۼ��ܷ�
            AllScore += Score;
        }
        AddPlayerScoreToUI("All", AllScore);
    }
}

// ��̬��� TextBlock �� VerticalBoxScores
void USettlementHUD::AddPlayerScoreToUI(FString PlayerName, int32 Score)
{
    if (VerticalBoxScores)
    {
        // ����һ���µ� TextBlock
        UTextBlock* NewTextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());

        // ���� TextBlock ���ı�����
        FString ScoreText = PlayerName + TEXT(": ") + FString::Printf(TEXT("%d"), Score) + TEXT("\n ");
        NewTextBlock->SetText(FText::FromString(ScoreText));

        // �� TextBlock ��ӵ� VerticalBox
        VerticalBoxScores->AddChildToVerticalBox(NewTextBlock);
    }
}




