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

    // ���ӷ���
    UFUNCTION(BlueprintCallable, Category = "Score")
    void IncreaseCustomScore(int32 Amount);

    // ��ȡ�Զ�������ķ���
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetCustomScore() const;

    // �����Զ�������ķ���
    UFUNCTION(BlueprintCallable, Category = "Score")
    void SetCustomScore(int32 NewScore);

    // ��ȡ��ǰѪ���ķ���
    UFUNCTION(BlueprintCallable, Category = "Health")
    int32 GetCurrentHealth() const;

    // ���õ�ǰѪ���ķ���
    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetCurrentHealth(int32 NewHealth);

    // ��д����� OnRep_Score ����
    virtual void OnRep_Score() override;

    // չʾ�������UI
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
    // �Զ���ķ��������������Ҫ�����Զ���ά����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 CustomScore;

    // ����������ֵ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    int32 MaxHealth;

    // ��ҵ�ǰ����ֵ
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
