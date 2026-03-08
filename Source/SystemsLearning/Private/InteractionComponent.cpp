#include "InteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformTrace(); // Performing Trace for every frame

	// ...
}

void UInteractionComponent::PerformTrace()
{
	//ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	//if (!OwnerCharacter) return;

	//UCameraComponent* Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();
	//if (!Camera) return;

	AActor* Owner = GetOwner();
	if (!Owner) return;
 
	FVector Start = Owner->GetActorLocation();
	FVector End = Start + (Owner->GetActorForwardVector() * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	// Debug
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1.f, 0, 0.5f);

	// if Trace hits, return the actor possibly door, or return null
	AActor* HitActor = bHit ? HitResult.GetActor() : nullptr; 

	if (HitActor != CurrentInteractable) {
		if (HitActor && HitActor->Implements<UInteractable>()) {
			SetCurrentInteractable(HitActor);
		}
		else {
			SetCurrentInteractable(nullptr);
		}
	}

	// Debug
	if (bHit && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Trace hit: %s"),
			*HitResult.GetActor()->GetName());
	}

}

void UInteractionComponent::SetCurrentInteractable(AActor* NewInteractable)
{
	CurrentInteractable = NewInteractable;
	OnInteractableChanged.Broadcast(CurrentInteractable);
}

void UInteractionComponent::TryInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("TryInteract called"));

	if (!CurrentInteractable) return;

	if (CurrentInteractable->Implements<UInteractable>()) {
		APlayerController* PC = Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController());

		IInteractable::Execute_OnInteract(CurrentInteractable, PC);
	}
}



