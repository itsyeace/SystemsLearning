#include "AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetComponents<UAttributeComponent>(Variants);

	if (Variants.Num() > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("More than 1 Attribute Component Found!"));
		return;
	}

	CurrentHealth = MaxHealth;

	AActor* MyOwner = GetOwner();
	if (!MyOwner) return;
	MyOwner->OnTakeAnyDamage.AddDynamic(this, &UAttributeComponent::HandleTakeAnyDamage);
	
}

void UAttributeComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);

	if (CurrentHealth <= 0.f) {
		// Death
		OnDeath.Broadcast();
	}
	
}

