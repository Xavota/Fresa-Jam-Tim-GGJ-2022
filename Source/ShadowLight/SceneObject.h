// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneObject.generated.h"

UCLASS()
class SHADOWLIGHT_API ASceneObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class USceneComponent* SceneCmp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UBoxComponent* BoxColl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UStaticMeshComponent* Sprite;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxCollisionSize = FVector(50.0f, 50.0f, 50.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D area;
};
