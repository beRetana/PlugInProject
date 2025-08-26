#pragma once

#include "Validators/IAssetValidator.h"

class FAssetNamingValidator : public IAssetValidator
{
public:

	FAssetNamingValidator(FString Prefix = TEXT("SM_")) : NameConventionPrefix(Prefix)
	{}

	virtual ~FAssetNamingValidator() = default;

	virtual void Validate(const TArray<FAssetData>& Assets, TArray<TArray<FAssetValidationData>>& OutValidationData) override;

	virtual void FillValidationData(FAssetValidationData& OutValidationData, const FAssetData& Asset) override;
	
	virtual void ApplySettings(const FAssetVerifierSettings& Settings) override;

	virtual FString GetConvention() const;

	virtual void ChangeConvention(const FString& NewConvention);

	virtual FName GetValidatorName() const override;

	static const TCHAR* ASSET_REGISTRY;

private:

	FString NameConventionPrefix;
	uint32 InvalidAssetsNum = 0;
	uint32 CheckedAssetsNum = 0;

	static const inline TCHAR* VALIDATOR_NAME = TEXT("Asset Naming Validator");
};