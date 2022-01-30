// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature_C.h"
#include "Kismet/GameplayStatics.h"
#include "Light2D.h"

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
  TArray<AActor*> found;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALight2D::StaticClass(), found);
  for (AActor* actor : found) {
    if (Cast<ALight2D>(actor)->isInLight(GetOwner()) != IsLight) {
      //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ded")));
      Die();
    }

  }
}

void UCreature_C::Die()
{
  IsAlive = false;
}

