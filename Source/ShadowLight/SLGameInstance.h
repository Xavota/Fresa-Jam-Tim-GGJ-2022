// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SLGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSceneObjectSaveData
{
  GENERATED_BODY()

	FVector position;
	bool DoorBoolean = false;
	bool PreasurePlateBoolean = false;
  bool PushBoolean = false;
  bool SwitchBoolean = false;
};

/**
 * 
 */
UCLASS()
class SHADOWLIGHT_API USLGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
  UFUNCTION(BlueprintCallable)
  void SaveObjectData(FString objectName, FSceneObjectSaveData data);
  UFUNCTION(BlueprintCallable)
  bool GetObjectData(FString objectName, FSceneObjectSaveData& data);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FSceneObjectSaveData> ObjectsData;
};
