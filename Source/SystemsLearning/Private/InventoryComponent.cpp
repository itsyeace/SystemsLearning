#include "InventoryComponent.h"
#include "ItemData.h"
#include "WorldItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxCapacity = 20;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::AddItem(UItemData* ItemData, int32 Quantity)
{

	if (!ItemData || Quantity <= 0) return; 

	if (ItemData->bIsStackable && HasItem(ItemData))
	{
		for (FInventorySlot& Slot : Items)
		{
			if (Slot.ItemData == ItemData)
			{
				int32 SpaceInStack = Slot.ItemData->MaxStackSize - Slot.Quantity;
				int32 AmountToAdd = FMath::Min(Quantity, SpaceInStack);

				if (AmountToAdd > 0)
				{
					Slot.Quantity += AmountToAdd;
					OnInventoryChanged.Broadcast();
					OnItemAdded.Broadcast(ItemData, Slot.Quantity);
				}
				return;
			}
		}
	}

	else 
	{
		FInventorySlot NewSlot;
		if (Items.Num() < MaxCapacity)
		{
			NewSlot.ItemData = ItemData;
			NewSlot.Quantity = Quantity;
			Items.Add(NewSlot);

			OnInventoryChanged.Broadcast();
			OnItemAdded.Broadcast(ItemData, Quantity);
			
		}
	}

	
}

void UInventoryComponent::RemoveItem(UItemData* ItemData, int32 Quantity)
{
	if (!ItemData) return;

	for (int32 i = 0; i<Items.Num(); i++) 
	{
		if (Items[i].ItemData == ItemData) 
		{
				Items[i].Quantity -= Quantity;
				if (Items[i].Quantity <= 0)
				{
					Items.RemoveAt(i);
				}
				OnInventoryChanged.Broadcast();
				return;
		}
	}
}

void UInventoryComponent::DropItem(UItemData* ItemData)
{
	if (!ItemData) return;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemData == ItemData)
		{
			FVector SpawnLocation = (GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 150.f));
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FTransform SpawnTransform(SpawnRotation, SpawnLocation);

			if (DroppedItem)
			{
				AWorldItem* NewItem = GetWorld()->SpawnActor<AWorldItem>(DroppedItem, SpawnTransform);

				if (NewItem)
				{ 
				NewItem->ItemData = ItemData;
				
				}
			}
			Items.RemoveAt(i);
			OnInventoryChanged.Broadcast();
			return;
		}
	}
}

bool UInventoryComponent::HasItem(UItemData* ItemData) const
{
	if (!ItemData) return false; 

	for (const FInventorySlot& Slot : Items) 
	{
		if (Slot.ItemData == ItemData) 
		{
			return true;
		}
	}

	return false;
}

