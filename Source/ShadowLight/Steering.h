// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Steering.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API USteering : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USteering();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float maxVelocity = 200;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float acelerationMultiplier = 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float maxAceleration = 100;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float aceptanceRadius = 50;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float arrivingRadius = 100;

	FVector2D velocity;

	FVector2D aceleration;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D pointToGo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D forward;
	
};
