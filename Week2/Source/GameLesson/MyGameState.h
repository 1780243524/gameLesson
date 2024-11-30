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

protected:
    virtual void Tick(float DeltaTime) override;
};
