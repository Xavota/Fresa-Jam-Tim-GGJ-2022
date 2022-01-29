// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch_C.h"

// Sets default values for this component's properties
USwitch_C::USwitch_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitch_C::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USwitch_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void USwitch_C::InitComponent(AActor* actorToActivate, TSubclassOf<AActor> classType, bool canDeactivate)
//{
//	SwitchActor = actorToActivate;
//	SwitchActorType = classType;
//	CanDeactivate = canDeactivate;
//}
void USwitch_C::InitComponent(bool canDeactivate)
{
	CanDeactivate = canDeactivate;
}

void USwitch_C::ToggleSwitchActive()
{
	if (!IsActive)
	{
		IsActive = true;
	}
	else
  {
    if (CanDeactivate)
    {
      IsActive = false;
    }
	}

	//if (SwitchActor)
	//{
	//  Cast<SwitchActorType>(SwitchActor);
	//	SwitchFunction(IsActive);
	//}
}

void USwitch_C::SetSwitchActive(bool active)
{
  IsActive = active;

  //if (SwitchFunction)
  //{
  //  SwitchFunction(IsActive);
  //}
}

bool USwitch_C::GetActive()
{
	return IsActive;
}

