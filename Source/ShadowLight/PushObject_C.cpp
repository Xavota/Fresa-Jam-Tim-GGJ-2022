// Fill out your copyright notice in the Description page of Project Settings.


#include "PushObject_C.h"

// Sets default values for this component's properties
UPushObject_C::UPushObject_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPushObject_C::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
}

