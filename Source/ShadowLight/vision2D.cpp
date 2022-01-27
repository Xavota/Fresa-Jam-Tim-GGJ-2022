// Fill out your copyright notice in the Description page of Project Settings.


#include "vision2D.h"
#include "Kismet/GameplayStatics.h"
#include "Movement_C.h"
#include "Steering.h"
#include "ShadowLightCharacter.h"
#include "Light2D.h"

// Sets default values for this component's properties
Uvision2D::Uvision2D()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Uvision2D::BeginPlay()
{
	Super::BeginPlay();

	
	

}


// Called every frame
void Uvision2D::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto pawn = Cast<APawn>(GetOwner());
	auto location = FVector2D(pawn->GetActorLocation().X,pawn->GetActorLocation().Y);
	auto steering = Cast<USteering>(pawn->GetComponentByClass(USteering::StaticClass()));
	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APawn::StaticClass(),found);
	TArray<AActor*> lights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ALight2D::StaticClass(),lights);
	ALight2D* light = nullptr;
	Line line;
	FVector2D result;
	if(lights.Num()>0){
		light = Cast<ALight2D>(lights[0]);
	}
	for(auto other : found){
		auto otherLocation = FVector2D(other->GetActorLocation().X,other->GetActorLocation().Y);
		auto dif = otherLocation-location;
		if(dif.Size()<distance && FVector2D::DotProduct(dif.GetSafeNormal(),steering->forward)>angle){
			line.setFromPoints(location,otherLocation);
			for(auto lin : light->lines){
				if(line.intersect(lin,result)){
					continue;
				}
			}
			if(Cast<AShadowLightCharacter>(other)){
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("detecting")));
				steering->pointToGo = otherLocation;
			}
		}
	}
}

