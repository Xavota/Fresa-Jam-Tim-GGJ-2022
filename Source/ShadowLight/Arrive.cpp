// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrive.h"
#include "Steering.h"
#include "Creature.h"

void UArrive::react(){
	auto pawn = Cast<ACreature>(GetOwner());

	auto steering = Cast<USteering>(pawn->GetComponentByClass(USteering::StaticClass()));

  if(steering->distance.Size()>arrivingRadius){
		steering->desiredVelocity *= (steering->distance.Size()-arrivingRadius)/(steering->aceptanceRadius-arrivingRadius);
	}
	else{
		steering->desiredVelocity *= 0;
	}
} 