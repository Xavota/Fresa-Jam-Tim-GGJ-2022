// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement_C.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"

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
      }

      if (DebugLine)
      {
        DrawDebugLine(
          GetWorld(),
          Start,
          End,
          FColor(255, 0, 0),
          false, 2.0f, 0,
          1.0f
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
      }

      if (DebugLine)
      {
        DrawDebugLine(
          GetWorld(),
          Start,
          End,
          FColor(255, 0, 0),
          false, 2.0f, 0,
          1.0f
        );
      }



      if (DebugData)
      {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, hitted || hitted2 ? "Hitted" : "Meh");
      }

      FVector directionalMovement = directions[i].GetAbs() * mov;
      if ((hitted || hitted2) && MinDistance < directionalMovement.Size())
      {
        //GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + directions[i] * (MinDistance - 10.0f));
      }
      else
      {
        GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + directionalMovement);
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

