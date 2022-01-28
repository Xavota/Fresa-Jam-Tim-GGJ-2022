// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reaction.h"
#include "Arrive.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Reactions), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API UArrive : public UReaction
{
	GENERATED_BODY()
	
	public:

	void react() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float arrivingRadius = 50;
};
