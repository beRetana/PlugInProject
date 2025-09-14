#pragma once

#include "AssetValidationData.h"

class FAssetReportGenerator
{
public:

	static void GenerateReport(VD::FAssetValidationReport& OutReport);

	static VD::FAssetValidationReport GenerateReport();

	static void ToCSV(const VD::FAssetValidationReport& ValidationData, FString& OutCSV);

	static FString ToCSV(const VD::FAssetValidationReport& Report);

	static FString ToJSON(const VD::FAssetValidationReport& Report);

	static void ToJSON(const VD::FAssetValidationReport& Report, FString& OutCSV);

	static void ToLog(const VD::FAssetValidationReport& Report, FString& OutLog);

	static FString ToLog(const VD::FAssetValidationReport& Report);

	static bool SaveSmallReportToCSVFile(const VD::FAssetValidationReport& Report);

	static bool SaveSmallReportToJSONFile(const VD::FAssetValidationReport& Report);

	static bool StreamSmallReportToLog(const VD::FAssetValidationReport& Report);

private:

	static void GenerateSummaryReportToCSV(const VD::FValidationReportSummary& Summary, FString& OutCSV);

	static void GenerateFullReportToCSV(const TMap<FName, VD::FFixerData>& ValidationData, FString& OutCSV);

	static void GenerateErrorsPerAssetToCSV(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutCSV);

	static void GenerateErrorsPerValidatorToCSV(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutCSV);
	
	static void GenerateSummaryReportToJSON(const VD::FValidationReportSummary& Report, FString& OutJSON);

	static void GenerateFullReportToJSON(const TMap<FName, VD::FFixerData>& ValidationData, FString& OutJSON);

	static void GenerateErrorsPerAssetToJSON(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutJSON);

	static void GenerateErrorsPerValidatorToJSON(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutJSON);

	static void GenerateSummaryReportToLog(const VD::FValidationReportSummary& Report, FString& OutLog);

	static void GenerateFullReportToLog(const TMap<FName, VD::FFixerData>& ValidationData, FString& OutLog);

	static void GenerateErrorsPerAssetToLog(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutLog);

	static void GenerateErrorsPerValidatorToLog(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutLog);

	static bool SaveStringAtomicallyToFile(const FString& Content, const FString& FilePath);
};