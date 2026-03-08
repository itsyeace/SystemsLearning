#include "EquipmentComponent.h"
#include "WorldItem.h"
#include "ItemData.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
}

void UEquipmentComponent::EquipItem(UItemData* ItemData, EEquipmentSlot Slot)
{
	if (!ItemData) return;

	if (IsSlotOccupied(Slot)) {
		UnequipItem(Slot);
	}

	EquippedItems.Add(Slot, ItemData);
	AWorldItem* AttachedItem = Cast<AWorldItem>(GetWorld()->SpawnActor(WorldItemClass));
	if (!AttachedItem) return;
	AttachedItem->SetItemMesh(ItemData->ItemMesh);
	AttachedActors.Add(Slot, AttachedItem);
	FName* FoundSocket = SocketNames.Find(Slot); 	
	if (!FoundSocket) return;

	AttachedItem->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, *FoundSocket);

	OnItemEquipped.Broadcast(ItemData, Slot);
}

void UEquipmentComponent::UnequipItem(EEquipmentSlot Slot)
{
	AWorldItem** FoundActor = AttachedActors.Find(Slot);
	
	if (FoundActor && *FoundActor)
	{
		(*FoundActor)->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		(*FoundActor)->MeshComponent->SetSimulatePhysics(true);
		(*FoundActor)->MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AttachedActors.Remove(Slot);
	}
	EquippedItems.Remove(Slot);
	OnItemUnequipped.Broadcast(Slot);
}

UItemData* UEquipmentComponent::GetEquippedItem(EEquipmentSlot Slot) const
{
	UItemData* const* FoundItem = EquippedItems.Find(Slot);

	if (FoundItem) {
		return *FoundItem;
	}

	return nullptr;
}

bool UEquipmentComponent::IsSlotOccupied(EEquipmentSlot Slot) const
{
	return EquippedItems.Contains(Slot);
}

