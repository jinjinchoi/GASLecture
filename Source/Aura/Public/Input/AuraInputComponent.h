// Copyright Jin

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(
		const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig)

	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.Inputag.IsValid())
		{
			if (PressedFunc)
			{
				UE_LOG(LogTemp, Warning, TEXT("PressedFunc InputTag: %s"), *Action.Inputag.ToString());
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.Inputag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.Inputag);
			}
			
			if (HeldFunc)
			{
				UE_LOG(LogTemp, Warning, TEXT("Binding HeldFunc with InputTag: %s"), *Action.Inputag.ToString());
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.Inputag);
			}
		}
	}
}
