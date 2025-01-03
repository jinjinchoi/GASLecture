// Copyright Jin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Engine/TargetPoint.h"
#include "AuraEnemySpawnPoint.generated.h"


class AAuraEnemy;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EnemyClass")
	TSubclassOf<AAuraEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EnemyClass")
	int32 EnemyLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EnemyClass")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
};
