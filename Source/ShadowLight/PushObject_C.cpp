// Fill out your copyright notice in the Description page of Project Settings.


#include "PushObject_C.h"

#include "SLGameInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPushObject_C::UPushObject_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game startsd
void UPushObject_C::BeginPlay()
{
	Super::BeginPlay();

  // ...
  FSceneObjectSaveData data;
  USLGameInstance* gInst = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
  if (gInst && gInst->GetObjectData(GetOwner()->GetFullName(), data))
  {
    GetOwner()->SetActorLocation(data.position);
  }
	
}


// Called every frame
void UPushObject_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPushObject_C::PushObject(FVector movement)
{
  GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + movement);

  USLGameInstance* gInst = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
  if (gInst)
  {
    FSceneObjectSaveData data;
    data.position = GetOwner()->GetActorLocation();
    gInst->SaveObjectData(GetOwner()->GetFullName(), data);
  }
}

