#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class UItemData;
class AWorldItem;

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	MainHand	UMETA(DisplayName = "Main Hand"), 
	OffHand		UMETA(DisplayName = "OffHand"),
	Head		UMETA(DisplayName = "Head"),
	Chest		UMETA(DisplayName = "Chest"),
	Legs		UMETA(DisplayName = "Legs"),
	Accessory	UMETA(DisplayName = "Accessory")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquipped, UItemData*, ItemData, EEquipmentSlot, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUnequipped, EEquipmentSlot, Slot);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYSTEMSLEARNING_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TMap<EEquipmentSlot, FName> SocketNames;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<AWorldItem> WorldItemClass;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipItem(UItemData* ItemData, EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnequipItem(EEquipmentSlot Slot);

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnItemEquipped OnItemEquipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnItemUnequipped OnItemUnequipped;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UItemData* GetEquippedItem(EEquipmentSlot Slot) const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool IsSlotOccupied(EEquipmentSlot Slot) const;

private:

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TMap<EEquipmentSlot, UItemData*> EquippedItems;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TMap<EEquipmentSlot, AWorldItem*> AttachedActors;

	UPROPERTY()
	USkeletalMeshComponent* CharacterMesh;
		
};
