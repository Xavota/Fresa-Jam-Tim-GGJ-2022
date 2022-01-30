// Fill out your copyright notice in the Description page of Project Settings.


#include "Door_C.h"

#include "SLGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "SceneObject.h"
#include "ShadowLightCharacter.h"
#include "Collition_C.h"

// Sets default values for this component's properties
UDoor_C::UDoor_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor_C::BeginPlay()
{
	Super::BeginPlay();

	// ...

  FSceneObjectSaveData data;
  USLGameInstance* gInst = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
  if (gInst && gInst->GetObjectData(GetOwner()->GetFullName(), data))
  {
    CanPass = data.DoorBoolean;
  }

  LoadSceneNames = { LoadSceneUp, LoadSceneRight, LoadSceneDown, LoadSceneLeft };
}

bool ChechLineTraceDoor(UBoxComponent* BoxColl, FVector Orientation,
                        FVector absDirR, float offset, float offsetR,
                        float distance, float& MinDistance, AActor** CloserActor,
                        UWorld* World,
                        FHitResult& Hit, FCollisionQueryParams& TraceParams)
{
  FVector Start = BoxColl->GetComponentLocation() + Orientation * offset + absDirR * offsetR;
  FVector End = Start + Orientation * distance;

  AShadowLightCharacter* ShadowChar = nullptr;
  bool hitted = false;
  do
  {
    hitted = World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldDynamic, TraceParams);
    if (hitted)
    {
      ShadowChar = Cast<AShadowLightCharacter>(Hit.GetActor());

      if (!ShadowChar)
      {
        TraceParams.AddIgnoredActor(Hit.GetActor());
      }
    }
  } while (hitted && !ShadowChar);

  DrawDebugLine(
    World,
    Start,
    End,
    FColor(255, 0, 0),
    false, -1, 0,
    5.0f
  );

  if (hitted && Hit.Distance < MinDistance)
  {
    MinDistance = Hit.Distance;
    *CloserActor = Hit.GetActor();

    return true;
  }
  return false;
}


// Called every frame
void UDoor_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (UnloadLevel)
  {
    UnloadLevel = false;
    UGameplayStatics::UnloadStreamLevel(this, UnloadSceneName, FLatentActionInfo(), true);
  }

	// ...
  if (CanPass)
  {
    TArray<FVector> Directions;
    Directions.Add(FVector::ForwardVector);
    Directions.Add(FVector::RightVector);
    Directions.Add(FVector::BackwardVector);
    Directions.Add(FVector::LeftVector);
    for (int i = 0; i < Directions.Num(); ++i)
    {
      if (LoadSceneNames[i] == "")
      {
        continue;
      }

      float MinDistance = 9999.9f;
      AActor* CloserActor = nullptr;


      ASceneObject* owner = Cast<ASceneObject>(GetOwner());
      FVector extents = owner->BoxColl->GetCollisionShape().GetBox();

      FVector absDir = Directions[i].GetAbs();
      FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);

      float offset = (extents * absDir).Size();
      float offsetR = (extents * absDirR).Size();
      float distance = 30.0f;

      FCollisionQueryParams TraceParams;
      FHitResult Hit;



      bool hitted = ChechLineTraceDoor(owner->BoxColl, Directions[i], absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);

      absDirR = -absDirR;

      bool hitted2 = ChechLineTraceDoor(owner->BoxColl, Directions[i], absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);



      if (hitted || hitted2)
      {
        AShadowLightCharacter* Character = Cast<AShadowLightCharacter>(CloserActor);
        if (Character)
        {
          UGameplayStatics::LoadStreamLevel(this, LoadSceneNames[i], true, true, FLatentActionInfo());
          //UGameplayStatics::UnloadStreamLevel(this, UnloadSceneName, FLatentActionInfo(), false);
          UnloadLevel = true;

          //Character->SetActorLocation(Character->GetActorLocation() - Directions[i] * 250.0f);
          Character->SetActorLocation(PositionAfterPass);
        }
      }
    }
  }
}

void UDoor_C::SetCanPass(bool can)
{
  CanPass = can;
  USLGameInstance* gInst = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
  if (gInst)
  {
    FSceneObjectSaveData data;
    data.DoorBoolean = CanPass;
    gInst->SaveObjectData(GetOwner()->GetFullName(), data);
  }
}

bool UDoor_C::PlayerIsTouching()
{
  TArray<FVector> Directions;
  Directions.Add(FVector::ForwardVector);
  Directions.Add(FVector::RightVector);
  Directions.Add(FVector::BackwardVector);
  Directions.Add(FVector::LeftVector);
  for (int i = 0; i < Directions.Num(); ++i)
  {
    float MinDistance = 9999.9f;
    AActor* CloserActor = nullptr;


    ASceneObject* owner = Cast<ASceneObject>(GetOwner());
    FVector extents = owner->BoxColl->GetCollisionShape().GetBox();

    FVector absDir = Directions[i].GetAbs();
    FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);

    float offset = (extents * absDir).Size();
    float offsetR = (extents * absDirR).Size();
    float distance = 30.0f;

    FCollisionQueryParams TraceParams;
    FHitResult Hit;



    bool hitted = ChechLineTraceDoor(owner->BoxColl, Directions[i], absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);

    absDirR = -absDirR;

    bool hitted2 = ChechLineTraceDoor(owner->BoxColl, Directions[i], absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);



    if (hitted || hitted2)
    {
      return true;
    }
  }
  return false;
}

