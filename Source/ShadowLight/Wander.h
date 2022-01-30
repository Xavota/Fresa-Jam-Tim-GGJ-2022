// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reaction.h"
#include "Wander.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Reactions), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API UWander : public UReaction
{
	GENERATED_BODY()
	
	public:
	void react() override;

	float timer=0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float distance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float range;
};
