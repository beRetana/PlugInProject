
#include "Validators/ValidatorManager.h"
#include "Validators/IAssetValidator.h"
#include "AssetValidationData.h"
#include "AssetVerifierSettings.h"

void FValidatorManager::ExecuteValidator(const FName& ValidatorName, const TArray<FAssetData>& Assets, FAssetValidationReport& ValidationReport)
{
	if (TUniquePtr<IAssetValidator>* Validator = ValidatorsMap.Find(ValidatorName))
	{
		if (Validator->IsValid()) 
		{
			Validator->Get()->Validate(Assets, ValidationReport);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Validator '%s' is not valid!"), *ValidatorName.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Validator '%s' is not found!"), *ValidatorName.ToString());
	}
}

void FValidatorManager::ExecuteValidators(const TArray<FName>& ValidatorsName, const TArray<FAssetData>& Assets, FAssetValidationReport& ValidationReport)
{
	for (const auto& ValidatorName : ValidatorsName)
	{
		ExecuteValidator(ValidatorName, Assets, ValidationReport);
	}
}

void FValidatorManager::ApplySettings(const FAssetVerifierSettings& Settings)
{
	for (auto& ValidatorPair : ValidatorsMap)
	{
		if (ValidatorPair.Value.IsValid())
		{
			ValidatorPair.Value->ApplySettings(Settings);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Validator '%s' is not valid!"), *ValidatorPair.Key.ToString());
		}
	}
}