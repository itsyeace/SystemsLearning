// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class IInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableChanged, AActor*, NewInteractable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableLost);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYSTEMSLEARNING_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Called by the player when interact pressed
	void TryInteract();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableChanged OnInteractableChanged; // Instantiating Delegate


private:

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TraceDistance = 300.f; // Setting it in Editor to 300.f

	// Should be Door for now
	UPROPERTY()
	AActor* CurrentInteractable = nullptr;

	void PerformTrace();
	void SetCurrentInteractable(AActor* NewInteractable);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
