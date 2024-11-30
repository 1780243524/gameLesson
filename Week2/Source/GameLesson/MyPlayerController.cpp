// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPlayerState.h"


AMyPlayerController::AMyPlayerController()
{
    // ����Ĭ������
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
    }
    // ��ȡ PlayerId
    int32 PlayerUniqueId = GetWorld()->GetFirstPlayerController()->PlayerState->GetPlayerId();

    // �����ҵ� PlayerId
    UE_LOG(LogTemp, Log, TEXT("Player Unique ID: %d"), PlayerUniqueId);
}
