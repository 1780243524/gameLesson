// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameLessonWeaponComponent.h"
#include "GameLessonCharacter.h"
#include "GameLessonProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGameLessonWeaponComponent::UGameLessonWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	// ��ʼ���ӵ���
	MaxAmmo = 30;  // Ĭ������ӵ���
	CurrentAmmo = MaxAmmo;

}


void UGameLessonWeaponComponent::Fire()
{
	// UE_LOG(LogTemp, Warning, TEXT("try fire!"));
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("No character"));
		return;
	}

	// ����ӵ���
	if (CurrentAmmo <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo!"));
		return; // �޷�����
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("start fire!"));
		// �����ӵ���
		CurrentAmmo--;
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// UE_LOG(LogTemp, Warning, TEXT("real fire!"));
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			// Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AGameLessonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

bool UGameLessonWeaponComponent::AttachWeapon(AGameLessonCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UGameLessonWeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// ���ý�ɫ�� WeaponComponent ����
	Character->WeaponComponent = this;

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UGameLessonWeaponComponent::Fire);
			  
			// ������װ������
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &UGameLessonWeaponComponent::Reload);
		}
	}
	return true;
}

void UGameLessonWeaponComponent::Reload()
{
	CurrentAmmo = MaxAmmo;
	UE_LOG(LogTemp, Log, TEXT("Reloaded! Current Ammo: %d"), CurrentAmmo);
}

void UGameLessonWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}