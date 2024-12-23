// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"


class AMyGameState;
class AGameLessonGameMode;
class UMyGameInstance;

/**
 *
 */
UCLASS()
class GAMELESSON_API AMyPlayerState : public APlayerState
{
    GENERATED_BODY()

public:

    AMyPlayerState();

    // 增加分数
    UFUNCTION(BlueprintCallable, Category = "Score")
    void IncreaseCustomScore(int32 Amount);

    // 获取自定义分数的方法
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetCustomScore() const;

    // 设置自定义分数的方法
    UFUNCTION(BlueprintCallable, Category = "Score")
    void SetCustomScore(int32 NewScore);

    // 获取当前血量的方法
    UFUNCTION(BlueprintCallable, Category = "Health")
    int32 GetCurrentHealth() const;

    // 设置当前血量的方法
    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetCurrentHealth(int32 NewHealth);

    // 重写父类的 OnRep_Score 方法
    virtual void OnRep_Score() override;

    // 展示结算分数UI
    UFUNCTION(BlueprintCallable, Category = "UI")
    void DisplaySettlement();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
    FString CustomPlayerName;

    FTimerHandle IsHitResetTimerHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
    bool bIsHit;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    void HitTarget();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ResetIsHit();

protected:
    // 自定义的分数变量（如果需要，可以额外维护）
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 CustomScore;

    // 玩家最大生命值
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    int32 MaxHealth;

    // 玩家当前生命值
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    int32 CurrentHealth;

    // void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

private:
    AMyGameState* MyGameState;
    AGameLessonGameMode* GameMode;
    UMyGameInstance* GameInstance;
};
