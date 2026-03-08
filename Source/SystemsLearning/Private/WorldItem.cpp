#include "WorldItem.h"
#include "ItemData.h"
#include "InventoryComponent.h"

// Sets default values
AWorldItem::AWorldItem()
{

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

}

// Called when the game starts or when spawned
void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
}

FText AWorldItem::GetInteractPrompt_Implementation() const
{
	if (!ItemData) return FText::FromString(TEXT("Pick Up"));

	return FText::Format(NSLOCTEXT("Interaction", "PickUpPrompt", "Pick Up {0}"), ItemData->ItemName);
}

void AWorldItem::SetItemMesh(UStaticMesh* NewMesh)
{
    if (!MeshComponent) return;

    MeshComponent->SetStaticMesh(NewMesh);
}

void AWorldItem::OnInteract_Implementation(APlayerController* Interactor)
{

    if (!Interactor) return;

    if (!ItemData) return;

    APawn* Pawn = Interactor->GetPawn();
    if (!Pawn) return;
    
    UInventoryComponent* Inventory = Pawn->FindComponentByClass<UInventoryComponent>();

    if (!Inventory) return;
    
    Inventory->AddItem(ItemData);
    Destroy();
}

