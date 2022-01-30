// Fill out your copyright notice in the Description page of Project Settings.


#include "SLGameInstance.h"

void USLGameInstance::SaveObjectData(FString objectName, FSceneObjectSaveData data)
{
  if (!ObjectsData.Contains(objectName))
  {
    ObjectsData.Add(TTuple<FString, FSceneObjectSaveData>(objectName, data));
  }
  else
  {
    ObjectsData[objectName] = data;
  }
}
bool USLGameInstance::GetObjectData(FString objectName, FSceneObjectSaveData& data)
{
  if (ObjectsData.Contains(objectName))
  {
    data = ObjectsData[objectName];
    return true;
  }
  return false;
}
