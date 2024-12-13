// Copyright Jin


#include "AbilitySystem/Data/LevelupInfo.h"

int32 ULevelupInfo::FindLevelForXP(const int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInformaion[1] = Level 1 Informaion;
		// LevelUpInformaion[2] = Level 1 Informaion;
		if (LevelUpInformation.Num() < Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
		
	}
	return Level;
}
