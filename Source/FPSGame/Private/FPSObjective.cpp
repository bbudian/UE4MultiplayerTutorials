// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjective.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSObjective::AFPSObjective()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPSObjective::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
}

void AFPSObjective::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFPSObjective::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter* character = Cast<AFPSCharacter>(OtherActor);
	if(character)
	{
		character->IsCarryingObjective = true;
		PlayEffects();

		Destroy();
	}

}

