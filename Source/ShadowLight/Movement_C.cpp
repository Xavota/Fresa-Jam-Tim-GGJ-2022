// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement_C.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "PushObject_C.h"

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

// Called every frame
void UMovement_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...

  FVector mov(Movement.X, Movement.Y, 0.0f);
  mov = mov.GetClampedToSize(0.0f, 1.0f) * MovementSpeed * DeltaTime;

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
    
        FVector absDir = directions[i].GetAbs();
        FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);
    
        float offset = (extents * absDir).Size();
        float offsetR = (extents * absDirR).Size();
        float distance = 100;
    
        AActor* CloserActor = nullptr;
    
        FVector Start;
        if (BoxColl)
        {
          BoxColl->GetCollisionShape().GetBox();
          Start = BoxColl->GetComponentLocation() + directions[i] * offset + absDirR * offsetR;
        }
        else
        {
          Start = GetOwner()->GetActorLocation() + directions[i] * offset;
        }
        FVector End = Start + directions[i] * distance;
    
        FCollisionQueryParams TraceParams;
        FHitResult Hit;
        bool hitted = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);
    
        if (hitted)
        {
          MinDistance = Hit.Distance;
          CloserActor = Hit.GetActor();
        }
    
        if (DebugLine)
        {
          DrawDebugLine(
            GetWorld(),
            Start,
            End,
            FColor(255, 0, 0),
            false, DebugLineTime, 0,
            DebugLineThickness
          );
        }
    
    
        absDirR = -absDirR;
    
        if (BoxColl)
        {
          BoxColl->GetCollisionShape().GetBox();
          Start = BoxColl->GetComponentLocation() + directions[i] * offset + absDirR * offsetR;
        }
        else
        {
          Start = GetOwner()->GetActorLocation() + directions[i] * offset;
        }
        End = Start + directions[i] * distance;
    
        bool hitted2 = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);
    
        if (hitted2 && Hit.Distance < MinDistance)
        {
          MinDistance = Hit.Distance;
          CloserActor = Hit.GetActor();
        }
    
        if (DebugLine)
        {
          DrawDebugLine(
            GetWorld(),
            Start,
            End,
            FColor(255, 0, 0),
            false, DebugLineTime, 0,
            DebugLineThickness
          );
        }
    
        if (DebugData)
        {
          GEngine->AddOnScreenDebugMessage(-1, DebugDataTime, FColor::Green, hitted || hitted2 ? "Hitted" : "Meh");
        }
    
        FVector directionalMovement = absDir * mov;
        if (!((hitted || hitted2) && MinDistance < directionalMovement.Size()))
        {
          GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + directionalMovement);
        }
        else
        {
          if (Pushing)
          {
            TArray<UActorComponent*> PushCs = CloserActor->GetComponentsByClass(UPushObject_C::StaticClass());
            if (PushCs.Num() != 0)
            {
              IsPushing = true;
              PushingActor = CloserActor;
              PushingDirection = directions[i];
            }
          }
        }
      }
    }
  }
  else
  {
    TArray<UActorComponent*> PushCs = PushingActor->GetComponentsByClass(UPushObject_C::StaticClass());
    
    if (PushCs.Num() != 0)
    {
      FVector posibleMovement = (PushingDirection.GetAbs() * mov + PushingDirection * mov.GetAbs()) * 0.5f;

      UBoxComponent* PushCollision = nullptr;

      if (posibleMovement.Size() > 0.0f)
      {
        TArray<UActorComponent*> PushColls = PushingActor->GetComponentsByClass(UBoxComponent::StaticClass());

        if (PushColls.Num() > 0)
        {
          PushCollision = Cast<UBoxComponent>(PushColls[0]);
        }
      }
      else
      {
        PushCollision = BoxColl;
      }

      UPushObject_C* PushCmp = Cast<UPushObject_C>(PushCs[0]);
    
      if (PushCmp && PushCollision)
      {
        FVector extents = PushCollision->GetCollisionShape().GetBox();

        float MinDistance = 9999.9f;

        FVector absDir = PushingDirection.GetAbs();
        FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);

        float offset = (extents * absDir).Size() + 5.0f;
        float offsetR = (extents * absDirR).Size();
        float distance = 100;

        AActor* CloserActor = nullptr;

        FVector Start;
        if (PushCollision)
        {
          PushCollision->GetCollisionShape().GetBox();
          Start = PushCollision->GetComponentLocation() + (absDir * mov).GetSafeNormal() * offset + absDirR * offsetR;
        }
        else
        {
          Start = GetOwner()->GetActorLocation() + (absDir * mov).GetSafeNormal() * offset;
        }
        FVector End = Start + (absDir * mov).GetSafeNormal() * distance;

        FCollisionQueryParams TraceParams;
        FHitResult Hit;
        bool hitted = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);

        if (hitted)
        {
          MinDistance = Hit.Distance;
          CloserActor = Hit.GetActor();
        }

        if (DebugLine)
        {
          DrawDebugLine(
            GetWorld(),
            Start,
            End,
            FColor(255, 0, 0),
            false, DebugLineTime, 0,
            DebugLineThickness
          );
        }


        absDirR = -absDirR;

        if (PushCollision)
        {
          PushCollision->GetCollisionShape().GetBox();
          Start = PushCollision->GetComponentLocation() + (absDir * mov).GetSafeNormal() * offset + absDirR * offsetR;
        }
        else
        {
          Start = GetOwner()->GetActorLocation() + (absDir * mov).GetSafeNormal() * offset;
        }
        End = Start + (absDir * mov).GetSafeNormal() * distance;

        bool hitted2 = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);

        if (hitted2 && Hit.Distance < MinDistance)
        {
          MinDistance = Hit.Distance;
          CloserActor = Hit.GetActor();
        }

        if (DebugLine)
        {
          DrawDebugLine(
            GetWorld(),
            Start,
            End,
            FColor(255, 0, 0),
            false, DebugLineTime, 0,
            DebugLineThickness
          );
        }

        if (DebugData)
        {
          GEngine->AddOnScreenDebugMessage(-1, DebugDataTime, FColor::Green, hitted || hitted2 ? "Hitted" : "Meh");
        }

        FVector directionalMovement = absDir * mov;
        if (DebugData)
        {
          GEngine->AddOnScreenDebugMessage(-1, DebugDataTime, FColor::Red, directionalMovement.ToString());
        }

        if (!((hitted || hitted2) && MinDistance < directionalMovement.Size()))
        {
          PushCmp->PushObject(directionalMovement * 0.5f);
          GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + directionalMovement * 0.5f);
        }

        //if (directionalMovement.Size() == 0.0f)
        //{
        //  IsPushing = false;
        //  PushingActor = nullptr;
        //  PushingDirection = FVector(0.0f, 0.0f, 0.0f);
        //
        //  if (DebugData)
        //  {
        //    GEngine->AddOnScreenDebugMessage(-1, DebugDataTime, FColor::Red, "Wrong Direction!");
        //  }
        //}
      }
    }

    if (!Pushing)
    {
      IsPushing = false;
      PushingActor = nullptr;
      PushingDirection = FVector(0.0f, 0.0f, 0.0f);
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

