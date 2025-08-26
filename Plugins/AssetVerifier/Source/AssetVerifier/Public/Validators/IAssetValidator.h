#pragma once

struct FAssetValidationData;
class FAssetVerifierSettings;

class IAssetValidator
{
public:
	virtual ~IAssetValidator() = default;
	virtual void Validate(const TArray<FAssetData>& Assets, TArray<TArray<FAssetValidationData>>& outValidationData) = 0;
	virtual FName GetValidatorName() const = 0;
	virtual void FillValidationData(FAssetValidationData& outValidationData, const FAssetData& Asset) = 0;
	virtual void ApplySettings(const FAssetVerifierSettings& Settings) = 0;

protected:
	IAssetValidator() = default;
};