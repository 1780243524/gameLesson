// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameLessonGameMode.h"
#include "GameLessonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GoldenScoreCube.h"
#include "RedScoreCube.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h" // ������ʱ��������
#include "MyPlayerState.h"
#include "MyPlayerController.h"
#include "MyGameState.h"

AGameLessonGameMode::AGameLessonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	BasicScore = 50;

	// ����Ĭ��ʱ������Ϊ 60 ��
	TimeLimit = 30.0f;
	TimeRemaining = TimeLimit;

	// �����������ֵ
	MaxHealth = 100;
	StartHealth = 100;
}

void AGameLessonGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ������ɼ�������
	SpawnRandomScoreCubes(5);  // ����������� 5 ������

	// ������ʱ��
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGameLessonGameMode::OnTimeUp, TimeLimit, false);
}

void AGameLessonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameLessonGameMode::OnTimeUp()
{
	// ��Ϸ����ʱ�����Ĳ��������㣩
	UE_LOG(LogTemp, Log, TEXT("Time's up! Game Over!"));

	// ������Ϸ
	EndGame();
}

float AGameLessonGameMode::GetTimeRemaining() const 
{
	return TimeRemaining;
}

int32 AGameLessonGameMode::GetMaxHealth() const 
{
	return MaxHealth;
}

int32 AGameLessonGameMode::GetStartHealth() const 
{
	return StartHealth;
}

void AGameLessonGameMode::DisplayScore() 
{
	// ��ȡ������ҵķ���
	AMyGameState* MyGameState = GetWorld() != nullptr ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
	if (MyGameState) 
	{
		TMap<FString, int32>PlayerScores = MyGameState->GetPlayerScores();
		for (const TPair<FString, int32>& Pair : PlayerScores)
		{
			FString PlayerName = Pair.Key;
			int32 Score = Pair.Value;
			// �����ҵ����ƺͷ���
			UE_LOG(LogTemp, Log, TEXT("Player: %s, Score: %d"), *PlayerName, Score);
		}
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController) 
		{
			AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerController->PlayerState);
			if (MyPlayerState) 
			{
				MyPlayerState->DisplaySettlement();
			}
		}
	}
	

}

void AGameLessonGameMode::EndGame()
{
	// ��Ϸ����ʱ�Ĵ��������磬��ͣ��Ϸ����ʾʤ��/ʧ�ܽ��棩
	// ��ʾ��ҵ÷֣�������������� HUD �� UMG UI ����ʾ�÷�
	DisplayScore();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetPause(true); // ��ͣ��Ϸ
	}
}

void AGameLessonGameMode::SpawnRandomScoreCubes(int32 Count)
{
	// ��ȡ��ǰ����
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < Count; i++)
		{
			// �������һ��û���ص���λ��
			FVector SpawnLocation = GetNonOverlappingLocation();

			// ���ѡ�� GoldenScoreCube �� RedScoreCube
			if (FMath::RandBool())  // ����� true������ GoldenScoreCube���������� RedScoreCube
			{
				World->SpawnActor<AGoldenScoreCube>(SpawnLocation, FRotator::ZeroRotator);
			}
			else
			{
				World->SpawnActor<ARedScoreCube>(SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
}

// ����Ƿ������� Actor �ص�
bool AGameLessonGameMode::CheckForOverlap(const FVector& Location)
{
	FHitResult HitResult;
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(FVector(100.f, 100.f, 100.f));
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);  // ���Ե�ǰ Actor

	// ʹ�� SweepSingleByChannel �������ײ
	return GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECC_Visibility, CollisionShape, QueryParams);
}

// ������ɲ�����ص�ֱ���ɹ�
FVector AGameLessonGameMode::GetNonOverlappingLocation()
{
	FVector RandomLocation = FVector(
		FMath::RandRange(100.0f, 2900.0f),  // ������� X ��λ��
		FMath::RandRange(100.0f, 2900.0f),  // ������� Y ��λ��
		50.0f  // �̶� Z ��߶�
	);

	// ���Զ������ֱ���ҵ�һ�����ص���λ��
	int32 AttemptCount = 0;
	while (CheckForOverlap(RandomLocation) && AttemptCount < 1)
	{
		// UE_LOG(LogTemp, Log, TEXT("Change Location!"));
		RandomLocation = FVector(
			FMath::RandRange(100.0f, 2900.0f),  // ������� X ��λ��
			FMath::RandRange(100.0f, 2900.0f),  // ������� Y ��λ��
			50.0f  // �̶� Z ��߶�
		);
		AttemptCount++;
	}

	return RandomLocation;  // �������յ�λ��
}