// Fill out your copyright notice in the Description page of Project Settings.


#include "RedScoreCube.h"
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
ARedScoreCube::ARedScoreCube()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // ʹ����ײ����Ϊ��ײ���
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // ������ײ����
    BoxComponent->SetCollisionProfileName("BlockAll");

    // ����ײ�¼��� OnHit ����
    BoxComponent->OnComponentHit.AddDynamic(this, &ARedScoreCube::OnHit);

    // ������̬���������ʹ�����ڹؿ��пɼ�
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Ϊ��������Ĭ�ϵľ�̬����
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMesh.Object);
    }

    // ���غ�ɫ����
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> RedMaterialFinder(TEXT("Material'/Game/Material/M_RedMaterial.M_RedMaterial'"));
    UE_LOG(LogTemp, Log, TEXT("Loading Red!"));
    if (RedMaterialFinder.Succeeded()) {
        UE_LOG(LogTemp, Log, TEXT("Red!"));
        UMaterialInterface* RedMaterial = RedMaterialFinder.Object;
        MeshComponent->SetMaterial(0, RedMaterial);
    }

    // ��������Ĳ���
    MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // �����������Ŵ�С
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // ֻ����ײ�д�����ײ

    // �����ص��¼�
    BoxComponent->SetNotifyRigidBodyCollision(true);

    // ��ʼ������
    HitCount = 0;
}

// Called when the game starts or when spawned
void ARedScoreCube::BeginPlay()
{
    Super::BeginPlay();
    // ȷ�������������
    if (MeshComponent)
    {
        // ��������ģ��
        MeshComponent->SetSimulatePhysics(true);

        // ��������
        MeshComponent->SetEnableGravity(true);

        // ��������
        MeshComponent->SetMassOverrideInKg(NAME_None, 10.0f);  // ��������Ϊ 10kg
    }
}

// Called every frame
void ARedScoreCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// ��Ͷ����ӵ��������������ʱ����
void ARedScoreCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
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
                    int32 ScoreToAdd = BasicScore;
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
