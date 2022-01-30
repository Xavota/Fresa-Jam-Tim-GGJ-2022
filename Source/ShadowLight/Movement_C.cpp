// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement_C.h"

#include "SLGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "PushObject_C.h"
#include "Collition_C.h"

// Sets default values for this component's properties
UMovement_C::UMovement_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovement_C::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

bool ChechLineTrace(UBoxComponent* BoxColl, FVector Orientation,
                    FVector absDirR, float offset, float offsetR,
                    float distance, float& MinDistance, AActor** CloserActor,
                    UWorld* World,
                    FHitResult& Hit, FCollisionQueryParams& TraceParams)
{
  FVector Start = BoxColl->GetComponentLocation() + Orientation * offset + absDirR * offsetR;
  FVector End = Start + Orientation * distance;

  TArray<UActorComponent*> Colls_C;
  bool hitted = false;
  do
  {
    hitted = World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);
    if (hitted)
    {
      Colls_C = Hit.GetActor()->GetComponentsByClass(UCollition_C::StaticClass());

      if (Colls_C.Num() <= 0)
      {
        TraceParams.AddIgnoredActor(Hit.GetActor());
      }
    }
  } while (hitted && Colls_C.Num() <= 0);

  if (hitted && Hit.Distance < MinDistance)
  {
    MinDistance = Hit.Distance;
    *CloserActor = Hit.GetActor();

    return true;
  }
  return false;
}

// Called every frame
void UMovement_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


  FVector mov(Movement.X, Movement.Y, 0.0f);
  mov = mov.GetClampedToSize(0.0f, 1.0f) * MovementSpeed * DeltaTime;
  // ...

  if (Pushing)
  {
    if (!IsPushing)
    {
      float MinDistance = 9999.9f;
      AActor* CloserActor = nullptr;



      FVector extents = BoxColl->GetCollisionShape().GetBox();

      FVector absDir = Orientation.GetAbs();
      FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);

      float offset = (extents * absDir).Size();
      float offsetR = (extents * absDirR).Size();
      float distance = 20.0f;

      FCollisionQueryParams TraceParams;
      FHitResult Hit;



      bool hitted = ChechLineTrace(BoxColl, Orientation, absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);

      absDirR = -absDirR;

      bool hitted2 = ChechLineTrace(BoxColl, Orientation, absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);



      if (hitted || hitted2)
      {
        TArray<UActorComponent*> PushCs = CloserActor->GetComponentsByClass(UPushObject_C::StaticClass());
        if (PushCs.Num() != 0)
        {
          IsPushing = true;
          PushingActor = CloserActor;
          PushingDirection = Orientation;
        }
      }
    }
  }
  else
  {
    IsPushing = false;
    PushingActor = nullptr;
    PushingDirection = FVector(0.0f, 0.0f, 0.0f);
  }

  if (mov.Size() > 0.0f)
  {
    Orientation = mov.GetSafeNormal();
  }



  if (!IsPushing)
  {
    if (mov.Size() > 0.0f)
    {
      FVector extents = BoxColl->GetCollisionShape().GetBox();
    
      TArray<FVector> directions;
      if (mov.X != 0.0f)
      {
        directions.Add(FVector::ForwardVector * (abs(mov.X) / mov.X));
      }
      if (mov.Y != 0.0f)
      {
        directions.Add(FVector::RightVector * (abs(mov.Y) / mov.Y));
      }
      for (int i = 0; i < directions.Num(); ++i)
      {
        float MinDistance = 9999.9f;
        AActor* CloserActor = nullptr;


    
        FVector absDir = directions[i].GetAbs();
        FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);
    
        float offset = (extents * absDir).Size();
        float offsetR = (extents * absDirR).Size();
        float distance = 100.0f;
    
        FCollisionQueryParams TraceParams;
        FHitResult Hit;



        bool hitted = ChechLineTrace(BoxColl, directions[i], absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);
    
        absDirR = -absDirR;

        bool hitted2 = ChechLineTrace(BoxColl, directions[i], absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);


    
        FVector directionalMovement = absDir * mov;
        if (!((hitted || hitted2) && MinDistance < directionalMovement.Size()))
        {
          GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + directionalMovement);
        }
      }
    }
  }
  else
  {
    TArray<UActorComponent*> PushCs = PushingActor->GetComponentsByClass(UPushObject_C::StaticClass());
    FVector posibleMovement = (PushingDirection.GetAbs() * mov + PushingDirection * mov.GetAbs()) * 0.5f;

    TArray<UBoxComponent*> PushCollisions;

    TArray<UActorComponent*> PushColls = PushingActor->GetComponentsByClass(UBoxComponent::StaticClass());
    if (PushColls.Num() > 0)
    {
      PushCollisions.Add(Cast<UBoxComponent>(PushColls[0]));
    }

    PushCollisions.Add(BoxColl);



    UPushObject_C* PushCmp = Cast<UPushObject_C>(PushCs[0]);
    
    if (PushCmp && PushCollisions.Num() > 0)
    {
      float MinDistance = 9999.9f;
      AActor* CloserActor = nullptr;
      bool hitted = false;

      FVector absDir = PushingDirection.GetAbs();
      FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);



      for (auto coll : PushCollisions)
      {
        FVector extents = coll->GetCollisionShape().GetBox();

        float offset = (extents * absDir).Size() + 5.0f;
        float offsetR = (extents * absDirR).Size();
        float distance = 100;

        FCollisionQueryParams TraceParams;
        FHitResult Hit;



        float TemDistance = 9999.9f;
        AActor* TemActor = nullptr;
        bool tempHitted = ChechLineTrace(coll, (absDir * mov).GetSafeNormal(), absDirR, offset, offsetR, distance, TemDistance, &TemActor, GetWorld(), Hit, TraceParams);
        if (tempHitted && TemDistance < MinDistance && TemActor != PushingActor)
        {
          MinDistance = TemDistance;
          CloserActor = TemActor;
          hitted = true;
        }

        absDirR = -absDirR;

        tempHitted = ChechLineTrace(coll, (absDir * mov).GetSafeNormal(), absDirR, offset, offsetR, distance, TemDistance, &TemActor, GetWorld(), Hit, TraceParams);
        if (tempHitted && TemDistance < MinDistance && TemActor != PushingActor)
        {
          MinDistance = TemDistance;
          CloserActor = TemActor;
          hitted = true;
        }
      }



      FVector directionalMovement = absDir * mov;
      if (!hitted || MinDistance >= directionalMovement.Size())
      {
        PushCmp->PushObject(directionalMovement * 0.5f);
        GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + directionalMovement * 0.5f);
      }
    }
  }
}

void UMovement_C::InitComponent(UBoxComponent* coll)
{
  BoxColl = coll;
}

void UMovement_C::Move(FVector2D movement)
{
  Movement = movement;
}

void UMovement_C::SetPushing(bool push)
{
  Pushing = push;
}

FVector UMovement_C::GetOrientation()
{
  return Orientation;
}

