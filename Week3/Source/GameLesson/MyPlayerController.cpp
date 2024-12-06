// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "GameLessonGameMode.h"

AMyPlayerController::AMyPlayerController()
{
    // ����Ĭ������
    bIsSettled = false;
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ��������ӳ�ʼ�����룬���ߴ������������߼�

    AMyPlayerState* MyState = GetPlayerState<AMyPlayerState>();
    if (MyState)
    {
        // ���ó�ʼ����
        MyState->SetCustomScore(0);
        // ��ȡ��ǰ��ҵ� PlayerId
        int32 PlayerUniqueId = GetPlayerState<AMyPlayerState>()->CustomPlayerId;
        // �����ҵ� PlayerId
        UE_LOG(LogTemp, Log, TEXT("Player Unique ID: %d"), PlayerUniqueId);
    }
}