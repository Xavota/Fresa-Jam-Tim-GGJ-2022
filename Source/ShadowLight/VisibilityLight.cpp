// Fill out your copyright notice in the Description page of Project Settings.


#include "VisibilityLight.h"
#include "Kismet/GameplayStatics.h"
#include "Light2D.h"
// Sets default values for this component's properties
UVisibilityLight::UVisibilityLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVisibilityLight::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVisibilityLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ALight2D::StaticClass(),found);
	ALight2D* light = nullptr;
	for(AActor* actor:found){
		light = Cast<ALight2D>(actor);
		//isInLight = light->isInLight(GetOwner());//&& Cast<ALight2D>(actor)->isInRange(FVector2D(GetOwner()->GetActorLocation().X,GetOwner()->GetActorLocation().Y));
	}
	if(light){

		visibility = light->intensityAt(GetOwner());

		/*visibility -= DeltaTime;
		if(visibility<0){
			visibility = 0;
		}*/
	}
	/*else{
		visibility += DeltaTime;
		if(visibility>1){
			visibility = 1;
		}
	}*/
	// ...
}

