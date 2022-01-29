// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Door_C.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API UDoor_C : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UFUNCTION(BlueprintCallable)
  virtual void SetCanPass(bool can);

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FName LoadSceneUp;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FName LoadSceneRight;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FName LoadSceneDown;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FName LoadSceneLeft;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FName UnloadSceneName;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FVector PositionAfterPass;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  bool CanPass = true;

  TArray<FName> LoadSceneNames;

  bool UnloadLevel = false;
  bool UnloadLevel2 = false;
};
