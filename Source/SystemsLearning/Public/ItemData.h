#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemTypeEnum : uint8
{
	Weapon		UMETA(DisplayName = "Weapon"), 
	Armor		UMETA(DisplayName = "Armor"),
	Consumable	UMETA(DisplayName = "Consumable"),
	Quest		UMETA(DisplayName = "Quest")
};

UCLASS()
class SYSTEMSLEARNING_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool bIsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (EditCondition = "bIsStackable", ClampMin = "1"))
	int32 MaxStackSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMesh* ItemMesh;
};
