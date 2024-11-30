// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

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

    // ��д����� OnRep_Score ����
    virtual void OnRep_Score() override;

    // չʾ�������UI
    void DisplayScore();


protected:
    // �Զ���ķ��������������Ҫ�����Զ���ά����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 CustomScore;

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    virtual void Tick(float DeltaTime) override;
private:

};
