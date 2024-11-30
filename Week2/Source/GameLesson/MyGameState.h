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
    // ����Ĭ��ֵ
    AMyGameState();
	
    // ʣ��ʱ��
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
    float TimeRemaining;

    // ��ȡʣ��ʱ��
    UFUNCTION(BlueprintCallable, Category = "Time")
    float GetTimeRemaining() const;

protected:
    virtual void Tick(float DeltaTime) override;
};
