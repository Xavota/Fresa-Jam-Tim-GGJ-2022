// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "Kismet/GameplayStatics.h"
#include "Light2D.h"
// Sets default values
ACreature::ACreature()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ALight2D::StaticClass(),found);
	for(AActor* actor:found){
		if(Cast<ALight2D>(actor)->isInLight(this)!=isLight){
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ded")));

		}
		
	}
}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
