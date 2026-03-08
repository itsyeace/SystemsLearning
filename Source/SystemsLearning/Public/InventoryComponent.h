#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;
class AWorldItem;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UItemData* ItemData = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity = 1;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UItemData*, AddedItem, int32, NewQuantity);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYSTEMSLEARNING_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")

	const TArray<FInventorySlot>& GetItems() const { return Items; } // const reference to the array

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxCapacity;

	UFUNCTION(BlueprintCallable)
	void AddItem(UItemData* ItemData, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UItemData* ItemData, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(UItemData* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(UItemData* ItemData) const;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemAdded OnItemAdded;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<AWorldItem> DroppedItem;

private:
	UPROPERTY()
	TArray<FInventorySlot> Items;
};
