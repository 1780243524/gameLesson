// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 *
 */
UCLASS()
class GAMELESSON_API AMyGameState : public AGameStateBase
{
    GENERATED_BODY()
public:
    // 设置默认值
    AMyGameState();

    // 剩余时间
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
    float TimeRemaining;

    // 获取剩余时间
    UFUNCTION(BlueprintCallable, Category = "Time")
    float GetTimeRemaining() const;

    // 在哈希表中保存玩家分数
    UPROPERTY()
    TMap<int32, int32> PlayerScores;

    // 更新分数表
    void UpdatePlayerScores(int32 PlayerId, int32 PlayerScore);

    // 得到分数表
    TMap<int32, int32> GetPlayerScores() const;

protected:
    virtual void Tick(float DeltaTime) override;
};
