// Copyright Jin


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"


FString UAuraProjectileSpell::GetDescription(int32 Level, const FGameplayTag& AbilityTag)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	if (Level == 1)
	{
		return UAuraAbilitySystemLibrary::GetAbilityDescription(GetWorld(), AbilityTag, Level);
	}
	else
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>\n\n Launched %d bolt of fire, exploding on impact and dealing <Damage>%d</> fire damage with a chance to burn\n\n <Small>Level: </><Level>%d </>"), FMath::Min(Level, NumProjectiles), Damage, Level);

	}
}

FString UAuraProjectileSpell::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	return FString::Printf(TEXT("<Title>NEXT LEVEL: </>\n\n Launched %d bolt of fire, exploding on impact and dealing <Damage>%d</> fire damage with a chance to burn\n\n <Small>Level: </><Level>%d </>"), FMath::Min(Level, NumProjectiles), Damage, Level);
}


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,  bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
	
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
	
	Projectile->DamageEffectSpecHandle = SpecHandle;
	
	Projectile->FinishSpawning(SpawnTransform);
	
}
