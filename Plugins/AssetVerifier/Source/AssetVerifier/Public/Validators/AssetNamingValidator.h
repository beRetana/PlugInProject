#pragma once

#include "Validators/IAssetValidator.h"

class FAssetNamingValidator : public IAssetValidator
{
public:

	FAssetNamingValidator(FString Prefix = TEXT("SM_")) : NameConventionPrefix(Prefix)
	{}

	virtual ~FAssetNamingValidator() = default;

	virtual void Validate(TArray<FAssetData>& Assets, TArray<FAssetValidationData>& OutValidationData) override;

	virtual void FillValidationData(FAssetValidationData& OutValidationData, const FAssetData& Asset) override;
	
	virtual void ApplySettings(const FAssetVerifierSettings& Settings) override;

	virtual FString GetConvention() const;

	virtual void ChangeConvention(const FString& NewConvention);

	virtual FString GetValidatorName() const override;

	static const TCHAR* ASSET_REGISTRY;

private:

	FString NameConventionPrefix;
	int32 InvalidAssetsNum = 0;
	int32 CheckedAssetsNum = 0;

	static const inline TCHAR* VALIDATOR_NAME = TEXT("Asset Naming Validator");
};