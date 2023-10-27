// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntropyLatentDebugActor.generated.h"

/**
 * This actor serves as a usage example for using EntropyLatent.
 * Drag this in your level to see the effects (a bunch of print statements in a specific order)
 */
UCLASS()
class ENTROPYLATENT_TEST_API AEntropyLatentDebugActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntropyLatentDebugActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Usage example for EntropyLatent
	void DoStuff();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
