// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reaction.h"
#include "Path.generated.h"

UCLASS( ClassGroup=(Reactions), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API UPath : public UReaction
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPath();

  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void react() override;

  UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> path;

	int actual = 0;
};
