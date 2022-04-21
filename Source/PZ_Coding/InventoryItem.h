#pragma once

#include "CoreMinimal.h"
#include "PZ_CodingCharacter.h"
//#include "Components/BoxComponent.h"
#include "InventoryItem.generated.h"

UCLASS(Blueprintable)
class PZ_CODING_API UInventoryItem : public UObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess = " true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess = " true"))
	class UBoxComponent* BoxCollision;
	
public:
	UInventoryItem();
	
	UPROPERTY(BlueprintReadWrite)
	FName Name;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float DistanceDrop;
	
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Icon;
	
	//virtual void InteractItem(APZ_CodingCharacter* Character );
	explicit UInventoryItem(FName Name);
	
};
