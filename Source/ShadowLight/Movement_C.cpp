// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement_C.h"

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
    FHitResult hit;
    GetOwner()->AddActorWorldOffset(mov, true, &hit);

    if (hit.bBlockingHit)
    {
      FVector norm(hit.Normal.X, hit.Normal.Y, 0.0f);

      norm.Normalize();

      mov = FVector::VectorPlaneProject(mov, norm) * (1.0f - hit.Time);
      GetOwner()->AddActorWorldOffset(mov, true);
    }
  }
}

void UMovement_C::Move(FVector2D movement)
{
  Movement = movement;
}

