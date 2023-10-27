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

	DoStuff();

	//Destroy();
}

void AEntropyLatentDebugActor::DoStuff()
{
	// Called immediately
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Started"));

	// Start a delay
	EntropyLatent::DelayTicks([]
	{
		// Called after 5 ticks 
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("After 5 Ticks"));
	}, 5);

	// Called in the same frame the delay was started
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("After latent Tick function"));

	// Start another delay (using game time)
	EntropyLatent::Delay<EntropyLatent::EDelayTimeType::GameTime>(
		// Capture this as a TStrongObjectPtr to prevent garbage collection
		// Any pointer to a UObject should always be captured as a TSSTrongObjectPtr or TWeakObjectPtr to prevent dangling pointers
		[This = TStrongObjectPtr{this}]
		{
			// Called after 2 seconds
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Delayed for 2 seconds"));

			// This check should theoretically not be necessary but better safe than sorry
			if (This)
			{
				// Gets called always as This is a TStrongObjectPtr
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Everything went well!"));
			}
		}, 2.f);

	// Start a delay for one tick
	EntropyLatent::DelayTicks(
		[This = TWeakObjectPtr<AEntropyLatentDebugActor>{this}]
		{
			// Called in the next tick
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Delayed for one tick"));

			// Capture This as TStrongObjectPtr to prevent garbage collection. We still need to check that it is valid as the object could have been garbage collected!
			if (TStrongObjectPtr This_Ptr{This.Get()})
			{
				// Do something with This_Ptr
				
				// Only called if the object was not garbage collected in the meantime
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Object is still alive"));
			}
		});

	// Still called in the same frame as the first print
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Still on the same frame"));

	// Call something on a different thread/UE task 
	EntropyLatent::ExecuteOnTask(
		// Capture this as a weak pointer to not prevent garbage collection but still prevent dangling pointers
		[This = TWeakObjectPtr{this}]
		{
			// To some heavy computation on a different thread
			// Thread-safety and synchronization have to be handled manually!!!

			// Return to game thread
			EntropyLatent::ExecuteOnGameThread(
				// We can't promote This to a TStrongObjectPtr in the capture as we are on a different thread!
				[This]
				{
					// Called on the game thread but after an unspecified time!
					
					// Now we promote and check for validity
					// As we are on the game thread, we should be able to get away with a normal TObjectPtr, but using TStrongObjectPtr is safer!
					if (TStrongObjectPtr This_Ptr{This.Get()})
					{
						// Called only if the object was not garbage collected
						
						// Do something with This_Ptr
						// We are back on the game thread, so thread safety is not an issue anymore
						
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Still alive"));
					}
				});
		});
}

// Called every frame
void AEntropyLatentDebugActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
