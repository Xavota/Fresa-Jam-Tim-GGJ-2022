// Fill out your copyright notice in the Description page of Project Settings.


#include "lightBlocker.h"
//#include "PaperSpriteComponent.h"
// Sets default values
AlightBlocker::AlightBlocker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("sprite"));
//	RootComponent = sprite;
}

// Called when the game starts or when spawned
void AlightBlocker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AlightBlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

