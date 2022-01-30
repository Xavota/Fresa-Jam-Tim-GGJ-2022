// Fill out your copyright notice in the Description page of Project Settings.


#include "Wander.h"
#include "Misc/App.h"
#include "Creature.h"
#include "Steering.h"
#include "Kismet/GameplayStatics.h"
#include "Light2D.h"


void UWander::react(){
  timer+=FApp::GetDeltaTime();
  if(timer >1){
    timer = 0;
    auto pawn = Cast<ACreature>(GetOwner());

	  auto steering = Cast<USteering>(pawn->GetComponentByClass(USteering::StaticClass()));

    auto location = FVector2D(pawn->GetActorLocation().X,pawn->GetActorLocation().Y);

    float angle = FMath::SRand()*6.28318530718;

	  steering->pointToGo = location + steering->forward*distance+FVector2D(cos(angle),sin(angle))*range;

	  TArray<AActor*> found;
	  UGameplayStatics::GetAllActorsOfClass(GetWorld(),ALight2D::StaticClass(),found);
    float actual = range;
    for(AActor* actor:found){
      auto light = Cast<ALight2D>(actor);
      while((light->isInRange(steering->pointToGo) && light->isPosInLight(steering->pointToGo))!=pawn->isLight){
		    actual += 6;
        angle = FMath::SRand()*6.28318530718;
        steering->pointToGo = location + steering->forward*distance+FVector2D(cos(angle),sin(angle))*actual;

      }
    }
    
	  

    
  }
}