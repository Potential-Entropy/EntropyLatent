// Fill out your copyright notice in the Description page of Project Settings.


#include "EntropyLatentDebugActor.h"

#include "EntropyLatent.h"

// Sets default values
AEntropyLatentDebugActor::AEntropyLatentDebugActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
}

// Called when the game starts or when spawned
void AEntropyLatentDebugActor::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Started"));
	EntropyLatent::DelayTicks([]
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("After 0 Ticks"));
	}, 5);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("After latent Tick function"));

	EntropyLatent::Delay<EntropyLatent::EDelayTimeType::GameTime, std::function<void()>>(
		[This = TStrongObjectPtr(this)]
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Delayed"));
			if (This)
			{
				This->RootComponent->Mobility = EComponentMobility::Movable;
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Everything went well!"));
			}
		}, 0.5f);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Done"));
	Destroy();
}

// Called every frame
void AEntropyLatentDebugActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
