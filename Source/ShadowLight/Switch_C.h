// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Switch_C.generated.h"

using foo = void (*)(bool);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHADOWLIGHT_API USwitch_C : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitch_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UFUNCTION(BlueprintCallable)
	void InitComponent(foo function, bool canDeactivate);
	//UFUNCTION(BlueprintCallable)
	//void SetActive(bool active);

	//UPROPERTY(BlueprintReadWrite)
	foo SwitchFunction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanDeactivate = false;
};
