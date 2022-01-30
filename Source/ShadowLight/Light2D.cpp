// Fill out your copyright notice in the Description page of Project Settings.


#include "Light2D.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "LightBlocker.h"
#include "SceneObject.h"
#include "Components/BoxComponent.h"


// Sets default values
ALight2D::ALight2D()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALight2D::BeginPlay()
{
	Super::BeginPlay();
	
}

bool 
ALight2D::isInLight(AActor* actor)
{
	return isPosInLight(FVector2D(actor->GetActorLocation().X,actor->GetActorLocation().Y));
}

bool ALight2D::isPosInLight(const FVector2D& _location)
{
	
	Line line;
	auto _locationShader=_location/resolution;
	line.setFromPoints(_locationShader,locationShader);
	for(Line& lin : lines){
		if(line.intersect(lin,result)){
			return false;
		}
	}
	return true;
}

float ALight2D::intensityAt(AActor* actor)
{
	auto _location = FVector2D(actor->GetActorLocation().X,actor->GetActorLocation().Y);
	float intensityAt = (_location-locationWorld).Size()/intensity;
	if(!isInLight(actor)){
		
		return 1;
	}
	if(intensityAt>1){
		return 1;
	}
	else if(intensityAt<difumination){
		return 0;
	}
	else{
		return (intensityAt-difumination)/(1.f-difumination);
	}
	
}

bool ALight2D::isInRange(const FVector2D& _location)
{
	if((_location-locationWorld).Size()>intensity){
		return false;
	}
	return true;
}

// Called every frame
void ALight2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*tris.Reset();
	auto world = GetWorld();
	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(world,AlightBlocker::StaticClass(),found);
	if(found.Num()==0){
		return;
	}
	auto blocker = Cast<AlightBlocker>(found[0]);
	
	auto center = blocker->GetActorLocation();

	std::vector<FVector> worldPoints{
		center+FVector(100,100,0),
		center+FVector(-100,100,0),
		center+FVector(100,-100,0),
		center+FVector(-100,-100,0),
	};

	std::vector<FColor> colors{
		FColor::Black,
		FColor::Green,
		FColor::Magenta,
		FColor::White
	
	};

	points = {FVector2D(worldPoints[0].X, worldPoints[0].Y),
						FVector2D(worldPoints[1].X, worldPoints[1].Y),
						FVector2D(worldPoints[2].X, worldPoints[2].Y),
						FVector2D(worldPoints[3].X, worldPoints[3].Y)};

	
	
	lines.resize(4);

	lines[0].setFromPoints(points[0],points[1]);
	lines[1].setFromPoints(points[1],points[3]);
	lines[2].setFromPoints(points[3],points[2]);
	lines[3].setFromPoints(points[2],points[0]);

	location = FVector2D(GetActorLocation().X,GetActorLocation().Y);
	
	
	bool colided;
	for(i=0;i<4;++i){
		actualLine.setFromPoints(location,points[i]);
		colided = false;
		for(o=0;o<4;++o){
			
			if(points[i]!=lines[o].start && points[i]!=lines[o].end){
				if(actualLine.intersect(lines[o],result) ){
					colided = true;
					break;
				}
			}
		}
		if(!colided){
			ordered.insert({atan2(points[i].Y,points[i].X),points[i]});
			DrawDebugLine(world,GetActorLocation(),worldPoints[i],colors[i]);

		}
	}

	/*for(std::pair<float,FVector2D> p : ordered){
		
	}*/

}

void ALight2D::calculateLight()
{
	
	tris.Reset();
	worldPoints.clear();
	points.clear();
	lines.clear();
	ordered.clear();
	temp.clear();
	auto world = GetWorld();
	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(world,ASceneObject::StaticClass(),found);

	locationWorld = FVector2D(GetActorLocation().X,GetActorLocation().Y);

	locationShader = locationWorld/resolution;

	float foundNum =found.Num();
	int actual = 0;
	for(i=0;i<foundNum;++i){
		auto object = Cast<ASceneObject>(found[i]);

		if(!object->blocksLight) continue;
		
		auto box = object->area;
		auto center = found[i]->GetActorLocation();

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f, y: %f"),center.X , center.Y));


		worldPoints.push_back(center+FVector(box.X*1.5f,box.Y*1.5f,0));
		worldPoints.push_back(center+FVector(-box.X*1.5f,box.Y*1.5f,0));
		worldPoints.push_back(center+FVector(box.X*1.5f,-box.Y*1.5f,0));
		worldPoints.push_back(center+FVector(-box.X*1.5f,-box.Y*1.5f,0));


		FVector2D point0 = FVector2D(worldPoints[actual*4+0].X, worldPoints[actual*4+0].Y)/resolution;
		FVector2D point1 = FVector2D(worldPoints[actual*4+1].X, worldPoints[actual*4+1].Y)/resolution;
		FVector2D point2 = FVector2D(worldPoints[actual*4+2].X, worldPoints[actual*4+2].Y)/resolution;
		FVector2D point3 = FVector2D(worldPoints[actual*4+3].X, worldPoints[actual*4+3].Y)/resolution;
		//if(!isInRange(point0)&&!isInRange(point1)&&!isInRange(point2)&&!isInRange(point3)) return;
		points.push_back(point0);
		points.push_back(point1);
		points.push_back(point2);
		points.push_back(point3);

		lines.push_back(Line());
		lines.push_back(Line());
		lines.push_back(Line());
		lines.push_back(Line());

		lines[actual*4+0].setFromPoints(points[actual*4+0],points[actual*4+1]);
		lines[actual*4+1].setFromPoints(points[actual*4+1],points[actual*4+3]);
		lines[actual*4+2].setFromPoints(points[actual*4+3],points[actual*4+2]);
		lines[actual*4+3].setFromPoints(points[actual*4+2],points[actual*4+0]);
		++actual;
	}


	points.push_back(FVector2D(0,0));
	points.push_back(FVector2D(-lightArea,0));
	points.push_back(FVector2D(0,-lightArea));
	points.push_back(FVector2D(-lightArea,-lightArea));

	lines.push_back(Line());
	lines.push_back(Line());
	lines.push_back(Line());
	lines.push_back(Line());
	
	lines[actual*4+0].setFromPoints(points[actual*4+0],points[actual*4+1]);
	lines[actual*4+1].setFromPoints(points[actual*4+1],points[actual*4+3]);
	lines[actual*4+2].setFromPoints(points[actual*4+3],points[actual*4+2]);
	lines[actual*4+3].setFromPoints(points[actual*4+2],points[actual*4+0]);
	
	
	bool colided;
	bool colided2;
	float minSize;
	FVector2D actualResult;
	
	FVector2D actualResult2;
	float actualAngle2;
	//bool colided2;
	for(i=0;i<actual*4+4;++i){
		actualLine.setFromPoints(locationShader,points[i]);
		colided = false;
		minSize = FLT_MAX;
		for(o=0;o<actual*4;++o){
			
			if(points[i]!=lines[o].start && points[i]!=lines[o].end){
				if(actualLine.intersect(lines[o],result) ){
					colided = true;
					FVector2D dif = result-locationShader;
					if(dif.Size()<minSize){
						minSize = dif.Size();
						actualResult = result;
						actualAngle = atan2(dif.Y,dif.X);
					}
					//
					//ordered.insert({atan2(dif.Y,dif.X),result});
					//ordered = 
					//break;
				}
			}
		}
		if(!colided){
			FVector2D dif = points[i]-locationShader;
			actualAngle = atan2(dif.Y,dif.X);
			ordered.insert({actualAngle,points[i]});
			//DrawDebugLine(world,GetActorLocation(),worldPoints[i],colors[i%4]);
			 angle1 = actualAngle + .01;

			 angle2 = actualAngle - .01;

			FVector2D vector1 = FVector2D(cos(angle1),sin(angle1))*lightArea*1.5f+locationShader;
			FVector2D vector2 = FVector2D(cos(angle2),sin(angle2))*lightArea*1.5f+locationShader;

			//DrawDebugLine(world,GetActorLocation(),FVector(vector1,worldPoints[i].Z),colors[i%4],false,-1.0,0,10);
			//DrawDebugLine(world,GetActorLocation(),FVector(vector1,worldPoints[i].Z),colors[i%4],false,-1.0,0,10);


			
			newLine1.setFromPoints(locationShader,vector1);
			newLine2.setFromPoints(locationShader,vector2);
			colided2 = false;
			minSize2 = FLT_MAX;
			for(Line& lin : lines){
				
				
				if(lin.intersect(newLine1,result2)){
					//DrawDebugLine(world,GetActorLocation(),FVector(result2,worldPoints[i].Z),colors[i%4],false,-1.0,0,10);

					FVector2D difer = result2-locationShader;
					//ordered.insert({atan2(difer.Y,difer.X),result2});
					colided2 = true;
					vecSize = difer.Size();
					if(minSize2>vecSize){
						minSize2 = vecSize;
						actualResult2 = result2;
						actualAngle2 = atan2(difer.Y,difer.X);
					}
					
				}

			}

			if(colided2){
				//DrawDebugLine(world,GetActorLocation(),FVector(actualResult2,worldPoints[i].Z),colors[i%4],false,-1.0,0,10);
				///if((points[i]-actualResult2).Size()>10)
				ordered.insert({actualAngle2,actualResult2});
			}

			colided2 = false;
			minSize2 = FLT_MAX;
			for(Line& lin : lines){
				
				
				if(lin.intersect(newLine2,result2)){
					//DrawDebugLine(world,GetActorLocation(),FVector(result2,worldPoints[i].Z),colors[i%4],false,-1.0,0,10);

					FVector2D difer = result2-locationShader;
					//ordered.insert({atan2(difer.Y,difer.X),result2});
					colided2 = true;
					vecSize = difer.Size();
					if(minSize2>vecSize){
						minSize2 = vecSize;
						actualResult2 = result2;
						actualAngle2 = atan2(difer.Y,difer.X);
					}
					
				}

			}

			if(colided2){
				//DrawDebugLine(world,GetActorLocation(),FVector(actualResult2,worldPoints[i].Z),colors[i%4],false,-1.0,0,10);
				///if((points[i]-actualResult2).Size()>10)
				ordered.insert({actualAngle2,actualResult2});
			}
		}
		else{
			//ordered.insert({actualAngle,actualResult});

		}
	}
	temp.resize(0);
	for(std::pair<float,FVector2D> p : ordered){
		temp.push_back(p.second);
	}
	int size = temp.size();
	for( i=0;i<size;++i){
		FCanvasUVTri tri;
		tri.V0_Pos = -locationShader;
		tri.V1_Pos = -temp[i];
		tri.V2_Pos = -temp[(i+1)%size];
		tri.V0_Color = FLinearColor::Green;
		tri.V1_Color = FLinearColor::Green;
		tri.V2_Color = FLinearColor::Green;
		tris.Add(tri);
	}
	//tris.SetNum(4);
}

void Line::setFromPoints(FVector2D _start, FVector2D _end)
{
	start = _start;
	end = _end;
	FVector2D dist = end-start;
	y = dist.X;
	x = -dist.Y;
	c = x*start.X+y*start.Y;
	
	magnitud = dist.Size();
}

bool Line::intersect(Line& other,FVector2D& result)
{
	float value = x*other.y-y*other.x;

	if(value==0){
		return false;
	}

	value = 1.0f/value;

	result.X = (c*other.y-other.c*y)*value;

	result.Y = (x*other.c-other.x*c)*value;

	return isInBounds(result) && other.isInBounds(result);
}

bool Line::isInBounds(FVector2D point)
{
	
	return FVector2D::Distance(point,start)<magnitud && FVector2D::Distance(point,end)<magnitud;
}

FVector2D Line::getPerpendicular()
{
	return FVector2D(x,y).GetSafeNormal();
}
