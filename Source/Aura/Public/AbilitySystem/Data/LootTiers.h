// Copyright Jin

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LootTiers|Spawning")
	TSubclassOf<AActor> LootClass;

	UPROPERTY(EditDefaultsOnly, Category="LootTiers|Spawning")
	float ChanceToSpawn = 0.f;

	UPROPERTY(EditDefaultsOnly, Category="LootTiers|Spawning")
	int32 MaxNumberToSpawn = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LootTiers|Spawning")
	bool bLootLevelOverride = true;
};

/**
 * 
 */
UCLASS()
class AURA_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FLootItem> GetLootItems();
	
	UPROPERTY(EditDefaultsOnly, Category="LootTiers|Spawning")
	TArray<FLootItem> LootItems;
	
};
