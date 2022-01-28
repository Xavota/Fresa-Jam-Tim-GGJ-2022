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

void USwitch_C::InitComponent(foo function, bool canDeactivate)
{
  SwitchFunction = function;
	CanDeactivate = canDeactivate;
}

//void USwitch_C::SetActive(bool active)
//{
//	if (SwitchFunction)
//	{
//		if (active)
//		{
//			SwitchFunction(true);
//		}
//		else
//    {
//		  if (CanDeactivate)	
//      {
//        SwitchFunction(false);
//			}
//		}
//	}
//}

