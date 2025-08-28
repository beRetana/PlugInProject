#pragma once

#include "Validators/IAssetValidator.h"

class FAssetNamingValidator : public IAssetValidator
{
public:

	FAssetNamingValidator(FName FixerName = TEXT("NamingFixer"), FString Prefix = TEXT("SM_")) :
		NameConventionPrefix(Prefix), FixerName(FixerName)
	{}

	virtual ~FAssetNamingValidator() = default;

	virtual void Validate(const TArray<FAssetData>& Assets, FAssetValidationReport& OutValidationReport) override;

	virtual void FillValidationData(const FAssetData& Asset, FAssetValidationData& OutValidationData) override;
	
	virtual void ApplySettings(const FAssetVerifierSettings& Settings) override;

	virtual FString GetConvention() const;

	virtual void ChangeConvention(const FString& NewConvention);

	virtual FName GetValidatorName() const override;

	virtual FName GetFixerName() const override;

	static const TCHAR* ASSET_REGISTRY;

private:

	FString NameConventionPrefix;
	FName FixerName;
	uint32 InvalidAssetsNum = 0;
	uint32 CheckedAssetsNum = 0;

	static const inline TCHAR* VALIDATOR_NAME = TEXT("Asset Naming Validator");
};