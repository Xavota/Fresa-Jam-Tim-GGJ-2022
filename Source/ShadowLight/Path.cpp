// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"
#include "Steering.h"
#include "Creature.h"

// Sets default values for this component's properties
UPath::UPath()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	auto pawn = Cast<ACreature>(GetOwner());

	auto steering = Cast<USteering>(pawn->GetComponentByClass(USteering::StaticClass()));

	steering->pointToGo = FVector2D(path[actual]->GetActorLocation().X,path[actual]->GetActorLocation().Y);
}

void UPath::react()
{
	++actual;
	actual %= path.Num();
}

