// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation_C.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UAnimation_C::UAnimation_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimation_C::BeginPlay()
{
	Super::BeginPlay();

  CurrentAnim = Animations.begin().Value();

  DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
  DynMaterial->SetTextureParameterValue("SpriteShit", CurrentAnim.Texture);
  FIntPoint texSize = CurrentAnim.Texture->GetImportedSize();
  DynMaterial->SetScalarParameterValue("TexWidth", texSize.X);
  DynMaterial->SetScalarParameterValue("TexHeight", texSize.Y);
  FVector2D frameSize = CurrentAnim.Frames[0].FrameSize;
  DynMaterial->SetScalarParameterValue("FrameWidth", frameSize.X);
  DynMaterial->SetScalarParameterValue("FrameHeight", frameSize.Y);
  FVector2D corner = CurrentAnim.Frames[0].FrameTopLeftCorner;
  DynMaterial->SetScalarParameterValue("LeftCorner", corner.X);
  DynMaterial->SetScalarParameterValue("TopCorner", corner.Y);

}


// Called every frame
void UAnimation_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TotalTime += DeltaTime;


  float timeForFrame = (1.0f / CurrentAnim.FramesPerSecond);
  if (TotalTime >= timeForFrame)
  {
    TotalTime -= timeForFrame;
    CurrentFrame = (CurrentFrame + 1) % CurrentAnim.Frames.Num();

    FVector2D frameSize = CurrentAnim.Frames[CurrentFrame].FrameSize;
    DynMaterial->SetScalarParameterValue("FrameWidth", frameSize.X);
    DynMaterial->SetScalarParameterValue("FrameHeight", frameSize.Y);
    FVector2D corner = CurrentAnim.Frames[CurrentFrame].FrameTopLeftCorner;
    DynMaterial->SetScalarParameterValue("LeftCorner", corner.X);
    DynMaterial->SetScalarParameterValue("TopCorner", corner.Y);

    FVector2D scale = CurrentAnim.Frames[CurrentFrame].RenderScale;
    StaticMeshCmp->SetRelativeScale3D(FVector(frameSize.X * scale.X, frameSize.Y * scale.Y, 1.0f));
    FVector2D center = CurrentAnim.Frames[CurrentFrame].FrameCenter;
    FVector loc(center.X * scale.X * 100.0f - frameSize.X * scale.X * 50.0f,
                center.Y * scale.Y * 100.0f - frameSize.Y * scale.Y * 50.0f,
                0.0f);
    StaticMeshCmp->SetRelativeLocation(FVector(loc.Y, loc.X, 0.0f));
  }
}

void UAnimation_C::InitComponent(UStaticMeshComponent* smCmp)
{
  StaticMeshCmp = smCmp;
  StaticMeshCmp->SetMaterial(0, DynMaterial);

  FVector2D frameSize = CurrentAnim.Frames[CurrentFrame].FrameSize;
  FVector2D scale = CurrentAnim.Frames[CurrentFrame].RenderScale;
  StaticMeshCmp->SetRelativeScale3D(FVector(frameSize.X * scale.X, frameSize.Y * scale.Y, 1.0f));
  FVector2D center = CurrentAnim.Frames[CurrentFrame].FrameCenter;
  FVector loc(center.X * scale.X * 100.0f - frameSize.X * scale.X * 50.0f,
              center.Y * scale.Y * 100.0f - frameSize.Y * scale.Y * 50.0f,
              0.0f);
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FVector(loc.Y, loc.X, 0.0f).ToString());
  StaticMeshCmp->SetRelativeLocation(FVector(loc.Y, loc.X, 0.0f));
}

void UAnimation_C::ChangeCurrentAnimation(FString animName)
{
  if (CurrentAnimName != animName)
  {
    CurrentAnimName = animName;
    CurrentAnim = Animations[animName];
    CurrentFrame = 0;

    FVector2D frameSize = CurrentAnim.Frames[CurrentFrame].FrameSize;
    DynMaterial->SetScalarParameterValue("FrameWidth", frameSize.X);
    DynMaterial->SetScalarParameterValue("FrameHeight", frameSize.Y);
    FVector2D corner = CurrentAnim.Frames[CurrentFrame].FrameTopLeftCorner;
    DynMaterial->SetScalarParameterValue("LeftCorner", corner.X);
    DynMaterial->SetScalarParameterValue("TopCorner", corner.Y);

    FVector2D scale = CurrentAnim.Frames[CurrentFrame].RenderScale;
    StaticMeshCmp->SetRelativeScale3D(FVector(frameSize.X * scale.X, frameSize.Y * scale.Y, 1.0f));
    FVector2D center = CurrentAnim.Frames[CurrentFrame].FrameCenter;
    FVector loc(center.X * scale.X * 100.0f - frameSize.X * scale.X * 50.0f,
      center.Y * scale.Y * 100.0f - frameSize.Y * scale.Y * 50.0f,
      0.0f);
    StaticMeshCmp->SetRelativeLocation(FVector(loc.Y, loc.X, 0.0f));
  }
}
