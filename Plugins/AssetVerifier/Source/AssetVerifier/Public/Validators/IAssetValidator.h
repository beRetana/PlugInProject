#pragma once

struct FAssetValidationData;
struct FAssetValidationReport;
struct FAssetData;
class FAssetVerifierSettings;

class IAssetValidator
{
public:
	virtual ~IAssetValidator() = default;
	virtual void Validate(const TArray<FAssetData>& Assets, FAssetValidationReport& ValidationReport) = 0;
	virtual FName GetValidatorName() const = 0;
	virtual FName GetFixerName() const = 0;
	virtual void FillValidationData(const FAssetData& Asset, FAssetValidationData& ValidationData) = 0;
	virtual void ApplySettings(const FAssetVerifierSettings& Settings) = 0;

protected:
	IAssetValidator() = default;
};