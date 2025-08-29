#pragma once

#include "CoreMinimal.h"
#include "Validators/IAssetValidator.h"

struct FAssetValidationReport;
struct FAssetData;

class FValidatorManager
{
public:

	void ExecuteValidator(const FName& ValidatorName, const TArray<FAssetData>& Assets, FAssetValidationReport& ValidationReport);
	void ExecuteValidators(const TArray<FName>& ValidatorsName, const TArray<FAssetData>& Assets, FAssetValidationReport& ValidationReport);
	void ApplySettings(const class FAssetVerifierSettings& Settings);

	template<typename TValidator, typename... TArgs>
	void RegisterValidator(const FName& ValidatorName, TArgs&&... Arguments)
	{
		static_assert(TIsDerivedFrom<TValidator, IAssetValidator>::IsDerived, "Class must inherit from IAssetValidator");

		if (ValidatorsMap.Contains(ValidatorName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Validator %s is already registered."), *ValidatorName.ToString());
			return;
		}

		ValidatorsMap.Add(ValidatorName, MakeUnique<TValidator>(Forward<TArgs>(Arguments)...));
	}

private:

	TMap<FName, TUniquePtr<IAssetValidator>> ValidatorsMap;
};
