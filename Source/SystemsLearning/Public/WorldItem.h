#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "WorldItem.generated.h"

class UItemData;
class UInventoryComponent;

UCLASS()
class SYSTEMSLEARNING_API AWorldItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UItemData* ItemData;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 Amount;

	UFUNCTION()
	virtual void OnInteract_Implementation(APlayerController* Interactor) override;

	UFUNCTION()
	virtual FText GetInteractPrompt_Implementation() const override;

	UFUNCTION()
	void SetItemMesh(UStaticMesh* NewMesh);
};
