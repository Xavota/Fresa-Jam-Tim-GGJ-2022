// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <map>
#include "Light2D.generated.h"

class Line{
 public:
	float x,y,c,magnitud;
	FVector2D start,end;
	void setFromPoints(FVector2D _start,FVector2D _end);
	bool intersect(Line& other,FVector2D& returl);
	bool isInBounds(FVector2D point);
	FVector2D getPerpendicular();
};


UCLASS()
class SHADOWLIGHT_API ALight2D : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALight2D();

	UFUNCTION(BlueprintCallable)
	bool
	isInLight(AActor* actor);

	UFUNCTION(BlueprintCallable)
	bool
	isPosInLight(const FVector2D& location);

	float
	intensityAt(AActor* actor);

	bool isInRange(const FVector2D& location);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void calculateLight();

	std::vector<FVector2D> points;
	std::vector<Line> lines;
	Line actualLine;

	UPROPERTY(BlueprintReadWrite)
	FVector2D locationWorld;

	//UPROPERTY(BlueprintReadWrite)
	//FVector2D locationShader;

	FVector2D dist;
	int o;
	int i;
	FVector2D result;
	FVector2D result2;
	float minSize2;
	float vecSize;
	std::vector<FVector> worldPoints;
	float actualAngle;
	float angle1,angle2;
	
	Line newLine1;
	Line newLine2;
	std::map<float,FVector2D> ordered;
	std::vector<FVector2D> temp;
  //TArray<FCanvasUVTri> tris;

	UPROPERTY(BlueprintReadWrite)
	TArray<FCanvasUVTri> tris;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> lightBlockers;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float intensity;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float difumination = .75;

	//UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float lightArea = 2048;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float resolution = 1;


};
