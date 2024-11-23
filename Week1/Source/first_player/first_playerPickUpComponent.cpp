// Copyright Epic Games, Inc. All Rights Reserved.

#include "first_playerPickUpComponent.h"

Ufirst_playerPickUpComponent::Ufirst_playerPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void Ufirst_playerPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &Ufirst_playerPickUpComponent::OnSphereBeginOverlap);
}

void Ufirst_playerPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	Afirst_playerCharacter* Character = Cast<Afirst_playerCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
