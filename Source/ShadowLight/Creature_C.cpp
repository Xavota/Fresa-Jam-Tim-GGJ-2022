// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature_C.h"
#include "Kismet/GameplayStatics.h"
#include "Light2D.h"
#include "Steering.h"

// Sets default values for this component's properties
UCreature_C::UCreature_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCreature_C::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCreature_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
  bool isInLight = false;
  TArray<AActor*> found;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALight2D::StaticClass(), found);
  for (AActor* actor : found) {
    isInLight |= Cast<ALight2D>(actor)->isInLight(GetOwner());

  }

  if (isInLight != IsLight)
  {
    Die();
  }
}

void UCreature_C::Die()
{
  UActorComponent* steerCmp = GetOwner()->GetComponentByClass(USteering::StaticClass());
  if (steerCmp)
  {
    Cast<USteering>(steerCmp)->maxVelocity = 0;
  }
  IsAlive = false;
}

