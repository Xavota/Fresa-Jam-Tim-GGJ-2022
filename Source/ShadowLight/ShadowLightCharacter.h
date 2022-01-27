// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShadowLightCharacter.generated.h"

UCLASS()
class SHADOWLIGHT_API AShadowLightCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShadowLightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveVertical(float value);
	UFUNCTION()
	void MoveHorizontal(float value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class USceneComponent* SceneCmp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UBoxComponent* BoxColl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UStaticMeshComponent* Sprite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UMovement_C* MovementComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerComponents)
	class UAnimation_C* AnimationCmp;

  UPROPERTY(BlueprintReadOnly)
	float VerticalMovement = 0.0f;
	UPROPERTY(BlueprintReadOnly)
	float HorizontalMovement = 0.0f;

	float MovementSpeed = 1000.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxCollisionSize = FVector(50.0f, 50.0f, 50.0f);
};
