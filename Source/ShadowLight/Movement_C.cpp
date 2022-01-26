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

  if (mov != FVector(0.0f, 0.0f, 0.0f))
  {
    float offset = 100;
    float distance = 500;
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
      FVector Start;
      if (BoxColl)
      {
        Start = BoxColl->GetComponentLocation() + directions[i] * offset;
      }
      else
      {
        Start = GetOwner()->GetActorLocation() + directions[i] * offset;
      }
      FVector End = Start + directions[i] * distance;

      FCollisionQueryParams TraceParams;
      FHitResult Hit;
      bool hitted = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);

      if (DebugData)
      {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, directions[i].ToString());
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Start.ToString());
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, End.ToString());
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, hitted ? "Hitted" : "Meh");
      }

      if (DebugLine)
      {
        DrawDebugLine(
          GetWorld(),
          Start,
          End,
          FColor(255, 0, 0),
          false, 100.0f, 0,
          10.0f
        );
      }
    }
  }

  if (mov.Size() > 0.0f)
  {
    GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + mov);

    //if (hit.bBlockingHit)
    //{
    //  FVector norm(hit.Normal.X, hit.Normal.Y, 0.0f);
    //
    //  norm.Normalize();
    //
    //  mov = FVector::VectorPlaneProject(mov, norm) * (1.0f - hit.Time);
    //  GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + mov);
    //}
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

