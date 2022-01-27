// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASceneObject::ASceneObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  SceneCmp = CreateDefaultSubobject<USceneComponent>("SceneCmp");
  RootComponent = SceneCmp;
  BoxColl = CreateDefaultSubobject<UBoxComponent>("Coll");
  BoxColl->SetupAttachment(SceneCmp);
  BoxColl->SetVisibility(true);
  BoxColl->SetHiddenInGame(false);
  BoxColl->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
  BoxColl->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
  Sprite = CreateDefaultSubobject<UStaticMeshComponent>("Sprite");
  Sprite->SetupAttachment(SceneCmp);
}

// Called when the game starts or when spawned
void ASceneObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  FVector loc = GetActorLocation();
  SetActorLocation(FVector(loc.X, loc.Y, loc.X * 0.01f + 150.0f));
}

