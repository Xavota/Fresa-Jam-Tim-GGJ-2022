// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "vision2D.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API Uvision2D : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Uvision2D();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

UPROPERTY(EditAnywhere,BlueprintReadWrite)
float distance = 0;

UPROPERTY(EditAnywhere,BlueprintReadWrite)
float angle = 0;
};
