// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowLightCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Movement_C.h"
#include "Animation_C.h"

// Sets default values
AShadowLightCharacter::AShadowLightCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCmp = CreateDefaultSubobject<USceneComponent>("SceneCmp");
  RootComponent = SceneCmp;
  BoxColl = CreateDefaultSubobject<UBoxComponent>("Coll");
  BoxColl->SetupAttachment(SceneCmp);
  BoxColl->SetVisibility(true);
  BoxColl->SetHiddenInGame(false);
  BoxColl->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
  Sprite = CreateDefaultSubobject<UStaticMeshComponent>("Sprite");
	Sprite->SetupAttachment(SceneCmp);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
  SpringArm->SetupAttachment(SceneCmp);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	MovementComp = CreateDefaultSubobject<UMovement_C>("MovementCmp");
	AnimationCmp = CreateDefaultSubobject<UAnimation_C>("AnimationCmp");
}

// Called when the game starts or when spawned
void AShadowLightCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimationCmp->InitComponent(Sprite);
}

// Called every frame
void AShadowLightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D mov(VerticalMovement, HorizontalMovement);
	MovementComp->Move(mov);

  if (mov != FVector2D(0.0f, 0.0f))
  {
    float offset = 100;
    float distance = 500;
    TArray<FVector> directions;
    if (mov.X != 0.0f)
    {
      directions.Add(FVector::ForwardVector * (abs(mov.X) / mov.X));
    }
    if (mov.Y != 0.0f)
    {
      directions.Add(FVector::RightVector * (abs(mov.Y) / mov.Y));
    }
    for (int i = 0; i < directions.Num(); ++i)
    {
      FVector Start;
      if (BoxColl)
      {
        Start = BoxColl->GetComponentLocation() + directions[i] * offset;
      }
      else
      {
        Start = GetActorLocation() + directions[i] * offset;
      }
      FVector End = Start + directions[i] * distance;
      
      FCollisionQueryParams TraceParams;
      FHitResult Hit;
      bool hitted = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, directions[i].ToString());
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Start.ToString());
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, End.ToString());
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, hitted ? "Hitted" : "Meh");
      
      DrawDebugLine(
        GetWorld(),
        Start,
        End,
        FColor(255, 0, 0),
        false, 100.0f, 0,
        10.0f
      );
    }
  }
}

// Called to bind functionality to input
void AShadowLightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShadowLightCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShadowLightCharacter::MoveHorizontal);
}

void AShadowLightCharacter::MoveVertical(float value)
{
  VerticalMovement = value;
}

void AShadowLightCharacter::MoveHorizontal(float value)
{
  HorizontalMovement = value;
}

