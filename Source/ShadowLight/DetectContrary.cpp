// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectContrary.h"
#include "Steering.h"
#include "Kismet/GameplayStatics.h"
#include "Light2D.h"
#include "Creature.h"
// Sets default values for this component's properties
UDetectContrary::UDetectContrary()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDetectContrary::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDetectContrary::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto pawn = Cast<ACreature>(GetOwner());
	auto steering = Cast<USteering>(pawn->GetComponentByClass(USteering::StaticClass()));
	steering->hasFear = false;
	auto location = FVector2D(pawn->GetActorLocation().X,pawn->GetActorLocation().Y);
	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ALight2D::StaticClass(),found);
	auto otherLocation = steering->desiredForward*distance+location;
	for(AActor* actor:found){
		auto light = Cast<ALight2D>(actor);
		if(light->isInRange(otherLocation)!=pawn->isLight){
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("going out")));

			steering->addForze((light->locationWorld-location).GetSafeNormal()*fear);
			continue;
		}
		if(light->isPosInLight(otherLocation)!=pawn->isLight){
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("detecting")));
			//steering->maxVelocity = 0;
			//steering->addForze(-steering->forward*fear);
			Line line;
			Line lin;
			line.setFromPoints(location,otherLocation);
			FVector2D ans;
			int size = light->temp.size();
			for(int i = 0; i < size;++i){
				lin.setFromPoints(light->temp[i],light->temp[(i+1)%size]);
				if(line.intersect(lin,ans)){
					auto rebote = lin.getPerpendicular();
					if(light->isPosInLight(ans+rebote)==pawn->isLight){
						rebote=-rebote;
					}
					steering->hasFear = true;;
					steering->nullifier = rebote;
					//steering->addForze(-rebote*fear);
				}
			}
		}
		
	}
	;
	// ...
}

