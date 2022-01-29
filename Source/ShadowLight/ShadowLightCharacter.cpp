// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowLightCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Movement_C.h"
#include "Animation_C.h"
#include "Collition_C.h"
#include "Switch_C.h"

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

bool ChechLineTraceCh(UBoxComponent* BoxColl, FVector Orientation,
                      FVector absDirR, float offset, float offsetR,
                      float distance, float& MinDistance, AActor** CloserActor,
                      UWorld* World,
                      FHitResult& Hit, FCollisionQueryParams& TraceParams)
{
  FVector Start = BoxColl->GetComponentLocation() + Orientation * offset + absDirR * offsetR;
  FVector End = Start + Orientation * distance;

  TArray<UActorComponent*> Colls_C;
  bool hitted = false;
  do
  {
    hitted = World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);
    if (hitted)
    {
      Colls_C = Hit.GetActor()->GetComponentsByClass(UCollition_C::StaticClass());

      if (Colls_C.Num() <= 0)
      {
        TraceParams.AddIgnoredActor(Hit.GetActor());
      }
    }
  } while (hitted && Colls_C.Num() <= 0);

  if (hitted && Hit.Distance < MinDistance)
  {
    MinDistance = Hit.Distance;
    *CloserActor = Hit.GetActor();

    return true;
  }
  return false;
}


// Called every frame
void AShadowLightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D mov(VerticalMovement, HorizontalMovement);
	MovementComp->Move(mov);

  FVector loc = GetActorLocation();
  SetActorLocation(FVector(loc.X, loc.Y, -loc.X * 0.1f + 150.0f));


  if (Interact)
  {
    Interact = false;

    float MinDistance = 9999.9f;
    AActor* CloserActor = nullptr;



    FVector Orientation = MovementComp->GetOrientation();

    FVector extents = BoxColl->GetCollisionShape().GetBox();

    FVector absDir = Orientation.GetAbs();
    FVector absDirR = FVector(absDir.Y, -absDir.X, 0.0f);

    float offset = (extents * absDir).Size();
    float offsetR = (extents * absDirR).Size();
    float distance = 20.0f;

    FCollisionQueryParams TraceParams;
    FHitResult Hit;



    bool hitted = ChechLineTraceCh(BoxColl, Orientation, absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);

    absDirR = -absDirR;

    bool hitted2 = ChechLineTraceCh(BoxColl, Orientation, absDirR, offset, offsetR, distance, MinDistance, &CloserActor, GetWorld(), Hit, TraceParams);



    if (hitted || hitted2)
    {
      TArray<UActorComponent*> Switch_C = CloserActor->GetComponentsByClass(USwitch_C::StaticClass());
      if (Switch_C.Num() != 0)
      {
        USwitch_C* switchObj = Cast<USwitch_C>(Switch_C[0]);
        switchObj->ToggleSwitchActive();
      }
    }
  }
}

// Called to bind functionality to input
void AShadowLightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShadowLightCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShadowLightCharacter::MoveHorizontal);

  PlayerInputComponent->BindAction("Push", IE_Pressed, this, &AShadowLightCharacter::PressPush);
  PlayerInputComponent->BindAction("Push", IE_Released, this, &AShadowLightCharacter::ReleasePush);
  PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AShadowLightCharacter::PressInteract);
  PlayerInputComponent->BindAction("Interact", IE_Released, this, &AShadowLightCharacter::ReleaseInteract);
}

void AShadowLightCharacter::MoveVertical(float value)
{
  VerticalMovement = value;
}

void AShadowLightCharacter::MoveHorizontal(float value)
{
  HorizontalMovement = value;
}

void AShadowLightCharacter::PressPush()
{
	if (MovementComp)
	{
		MovementComp->SetPushing(true);
	}
}

void AShadowLightCharacter::ReleasePush()
{
  if (MovementComp)
  {
    MovementComp->SetPushing(false);
  }
}

void AShadowLightCharacter::PressInteract()
{
  Interact = true;
}

void AShadowLightCharacter::ReleaseInteract()
{
}

