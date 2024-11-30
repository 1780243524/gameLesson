// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenScoreCube.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameLessonProjectile.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerState.h"
#include "GameLessonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoldenScoreCube::AGoldenScoreCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // ʹ����ײ����Ϊ��ײ���
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // ������ײ����
    BoxComponent->SetCollisionProfileName("BlockAll");

    // ����ײ�¼��� OnHit ����
    BoxComponent->OnComponentHit.AddDynamic(this, &AGoldenScoreCube::OnHit);

    // ������̬���������ʹ�����ڹؿ��пɼ�
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Ϊ��������Ĭ�ϵľ�̬����
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMesh.Object);
    }

    // ���ؽ�ɫ����
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> GoldenMaterialFinder(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold'"));
    UE_LOG(LogTemp, Log, TEXT("Loading Golden!"));
    if (GoldenMaterialFinder.Succeeded()) {
        UE_LOG(LogTemp, Log, TEXT("Golden!"));
        UMaterialInterface* GoldenMaterial = GoldenMaterialFinder.Object;
        MeshComponent->SetMaterial(0, GoldenMaterial);
    }


    // ��������Ĳ���
    MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // �����������Ŵ�С
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // ֻ����ײ�д�����ײ

    // ��ʼ������
    HitCount = 0;
}

// Called when the game starts or when spawned
void AGoldenScoreCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldenScoreCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// ��Ͷ����ӵ��������������ʱ����
void AGoldenScoreCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
    // �����ײ�����������Ƿ���Ͷ����ӵ���
    // ��ȡ��ǰ�� GameMode ʵ��
    
    if (OtherActor && OtherActor->IsA(AGameLessonProjectile::StaticClass())) {
        // ��ȡ���Ͷ��������
        if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
            // �� PlayerState ǿ��ת��Ϊ AMyPlayerState
            AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerController->PlayerState);
            if (MyPlayerState)
            {
                // ���ӷ���
                // ��ȡ GameMode �е� BasicScore ����
                AGameLessonGameMode* GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));
                if (GameMode) {
                    int32 BasicScore = GameMode->BasicScore;
                    int32 ScoreToAdd = BasicScore * 2;
                    MyPlayerState->IncreaseCustomScore(ScoreToAdd);
                    UE_LOG(LogTemp, Log, TEXT("CustomScore Increased by hitting ScoreCube! Score Added: %d"), ScoreToAdd);
                }
                
            }
        }

        // ����Ͷ����
        OtherActor->Destroy();

        // ���ӱ����еĴ���
        HitCount++;

        // ���ݱ����еĴ���ִ�в�ͬ�Ĳ���
        if (HitCount == 1) {
            // ��һ�α�����ʱ����С�����СΪԭ���� 1/2
            FVector CurrentScale = MeshComponent->GetComponentScale();
            MeshComponent->SetWorldScale3D(CurrentScale * 0.5f);
            UE_LOG(LogTemp, Log, TEXT("ScoreCube hit once, scale reduced to half!"));
        }
        else if (HitCount >= 2) {
            // �ڶ��α�����ʱ�����ٷ���
            UE_LOG(LogTemp, Log, TEXT("ScoreCube hit twice, destroyed!"));
            Destroy();
        }
    }
}
