#pragma once

#include "AssetValidationData.h"

class FAssetReportGenerator
{
public:

	static FAssetValidationReport GenerateReport(const TArray<FAssetValidationData>& ValidationData);

	inline FString ToCSV(const FAssetValidationReport& Report);

	inline FString ToJSON(const FAssetValidationReport& Report);

	inline FString ToLog(const FAssetValidationReport& Report);
};