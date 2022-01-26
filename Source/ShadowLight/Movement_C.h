// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Movement_C.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API UMovement_C : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovement_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void InitComponent(class UBoxComponent* coll);

	UFUNCTION(BlueprintCallable)
	virtual void Move(FVector2D movement);


  FVector2D Movement;
  class UBoxComponent* BoxColl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementData)
  float MovementSpeed = 1000.0f;


  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool DebugLine = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool DebugData = false;
};
