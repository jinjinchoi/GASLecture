// Copyright Jin


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag AbilityTag, bool bLogNotFound)
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Ability Tag not found"));
	}
	
	return FAuraAbilityInfo();
}
