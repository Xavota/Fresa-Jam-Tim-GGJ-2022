// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowLightCharacter.h"
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
  BoxColl->InitBoxExtent(BoxCollisionSize);
	BoxColl->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
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

  BoxColl->InitBoxExtent(BoxCollisionSize);
	MovementComp->InitComponent(BoxColl);
	AnimationCmp->InitComponent(Sprite);
}

// Called every frame
void AShadowLightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D mov(VerticalMovement, HorizontalMovement);
	MovementComp->Move(mov);

  FVector loc = GetActorLocation();
  SetActorLocation(FVector(loc.X, loc.Y, -loc.X * 0.1f + 150.0f));
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

