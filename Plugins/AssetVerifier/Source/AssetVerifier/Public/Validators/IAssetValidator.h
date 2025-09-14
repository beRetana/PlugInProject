#pragma once

#include "AssetValidationData.h"
#include "AssetVerifierSettings.h"
#include "AssetRegistry/AssetData.h"

class IAssetValidator
{
public:
	virtual ~IAssetValidator() = default;
	virtual void Validate(const TArray<FAssetData>& Assets, VD::FAssetValidationReport& ValidationReport) = 0;
	virtual FName GetValidatorName() const = 0;
	virtual FName GetFixerName() const = 0;
	virtual void FillValidationData(const FAssetData& Asset, VD::FAssetValidationData& ValidationData) = 0;
	virtual void ApplySettings(const FAssetVerifierSettings& Settings) = 0;

protected:
	IAssetValidator() = default;
};