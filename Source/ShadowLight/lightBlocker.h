// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "lightBlocker.generated.h"

class UPaperSpriteComponent;

UCLASS()
class SHADOWLIGHT_API AlightBlocker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AlightBlocker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperSpriteComponent* sprite;*/
};
