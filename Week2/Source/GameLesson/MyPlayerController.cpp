// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPlayerState.h"


AMyPlayerController::AMyPlayerController()
{
    // 设置默认属性
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 在这里添加初始化代码，或者处理玩家输入的逻辑

    AMyPlayerState* MyState = GetPlayerState<AMyPlayerState>();
    if (MyState)
    {
        // 设置初始分数
        MyState->SetCustomScore(0);
    }
    // 获取 PlayerId
    int32 PlayerUniqueId = GetWorld()->GetFirstPlayerController()->PlayerState->GetPlayerId();

    // 输出玩家的 PlayerId
    UE_LOG(LogTemp, Log, TEXT("Player Unique ID: %d"), PlayerUniqueId);
}
