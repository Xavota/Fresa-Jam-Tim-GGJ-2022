// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animation_C.generated.h"

USTRUCT(BlueprintType)
struct FAnimation2DFrame
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D FrameTopLeftCorner;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D FrameSize;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D FrameCenter;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D RenderScale;
};

USTRUCT(BlueprintType)
struct FAnimation2D
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Texture;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<FAnimation2DFrame> Frames;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float FramesPerSecond;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API UAnimation_C : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimation_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void InitComponent(class UStaticMeshComponent* smCmp);

	
	UFUNCTION(BlueprintCallable)
	virtual void ChangeCurrentAnimation(FString animName);

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* Material;
	class UMaterialInstanceDynamic* DynMaterial;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FAnimation2D> Animations;

	float TotalTime = 0.0f;
  int CurrentFrame = 0;
  FAnimation2D CurrentAnim;
  FString CurrentAnimName;

	class UStaticMeshComponent* StaticMeshCmp;
};
