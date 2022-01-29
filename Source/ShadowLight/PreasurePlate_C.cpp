// Fill out your copyright notice in the Description page of Project Settings.


#include "PreasurePlate_C.h"
#include "Creature.h"
#include "ShadowLightCharacter.h"
#include "SceneObject.h"
#include "Collition_C.h"

// Sets default values for this component's properties
UPreasurePlate_C::UPreasurePlate_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPreasurePlate_C::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPreasurePlate_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
  bool pressed = false;

  TArray<AActor*> Result;
  GetOwner()->GetOverlappingActors(Result, ACreature::StaticClass());

  for (auto act : Result)
  {
    if (!Cast<AShadowLightCharacter>(act))
    {
      pressed = true;
      break;
    }
  }

  if (!pressed)
  {
    TArray<AActor*> Result2;
    GetOwner()->GetOverlappingActors(Result2, ASceneObject::StaticClass());

    for (auto act : Result2)
    {
      TArray<UActorComponent*> Colls_C = act->GetComponentsByClass(UCollition_C::StaticClass());
      if (Colls_C.Num() > 0)
      {
        pressed = true;
        break;
      }
    }
  }

  SetSwitchActive(pressed);

}

//void UPreasurePlate_C::InitComponent(AActor* actorToActivate, TSubclassOf<AActor> classType, bool canDeactivate)
//{
//	SwitchActor = actorToActivate;
//	SwitchActorType = classType;
//	CanDeactivate = canDeactivate;
//}
void UPreasurePlate_C::InitComponent(bool canDeactivate)
{
  CanDeactivate = canDeactivate;
}

void UPreasurePlate_C::ToggleSwitchActive()
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

void UPreasurePlate_C::SetSwitchActive(bool active)
{
  IsActive = active;

  //if (SwitchFunction)
  //{
  //  SwitchFunction(IsActive);
  //}
}

bool UPreasurePlate_C::GetActive()
{
  return IsActive;
}

