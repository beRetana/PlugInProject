#pragma once

#include "Containers/Map.h"

class FValidatorManager
{
public:

	void ExecuteValidator(const FName& ValidatorName, TArray<FAssetData>& Assets, TArray<struct FAssetValidationData>& ValidationData);
	void ExecuteValidators(const TArray<FName>& ValidatorsName, TArray<FAssetData>& Assets, TArray<struct FAssetValidationData>& ValidationData);
	void ApplySettings(const class FAssetVerifierSettings& Settings);

	template<typename TValidator, typename... TArgs>
	void RegisterValidator(const FName& ValidatorName, TArgs&&... Arguments)
	{
		static_assert(TIsDerivedFrom<TValidator, class IAssetValidator>::IsDerived, "Class must inherit from IAssetValidator");

		if (ValidatorsMap.Contains(ValidatorName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Validator %s is already registered."), *ValidatorName.ToString());
			return;
		}

		ValidatorsMap.Add(ValidatorName, MakeUnique<TValidator>(Forward<TArgs>()...));
	}

private:

	TMap<FName, TUniquePtr<class IAssetValidator>> ValidatorsMap;
};
