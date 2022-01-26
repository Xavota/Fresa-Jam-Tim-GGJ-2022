// Fill out your copyright notice in the Description page of Project Settings.


#include "Steering.h"
#include "Movement_C.h"
//#include "Enemy.h"

// Sets default values for this component's properties
USteering::USteering()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void USteering::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void 
USteering::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(DeltaTime>=1.f/60.f){
		DeltaTime = 1.f/60.f;
	}

	auto pawn = Cast<APawn>(GetOwner());

	//if(pawn->isDead) return ;

	FVector2D location(pawn->GetActorLocation().X,pawn->GetActorLocation().Y);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f %f"),pointToGo.X,pointToGo.Y));

	FVector2D distance = pointToGo-location;

	FVector2D desiredVelocity = distance.GetSafeNormal()*maxVelocity;

	if(distance.Size()<aceptanceRadius){
		desiredVelocity *=0;
	}
	else if(distance.Size()<arrivingRadius){
		desiredVelocity *= (distance.Size()-aceptanceRadius)/(arrivingRadius-aceptanceRadius);
	}


	aceleration = (desiredVelocity - velocity)*acelerationMultiplier;

	if(aceleration.Size() > maxAceleration){
		aceleration = aceleration.GetSafeNormal()*maxAceleration;
	}

	velocity += aceleration*maxAceleration*DeltaTime;

	if(velocity.Size() > maxVelocity){
		velocity = velocity.GetSafeNormal()*maxVelocity;
	}

	//pawn->AddActorWorldOffset(FVector(DeltaTime*velocity.X,DeltaTime*velocity.Y,0),true);
	auto movement = Cast<UMovement_C>(pawn->GetComponentByClass(UMovement_C::StaticClass()));
	movement->Move(velocity);
	movement->MovementSpeed = velocity.Size();
	if(velocity.Size()>1){
		forward = velocity.GetSafeNormal();
		
	}
	
}


