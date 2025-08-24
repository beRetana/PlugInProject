#pragma once

#include "AssetValidationData.h"

class FAssetReportGenerator
{
public:

	static void GenerateReport(TArray<FAssetValidationData>& ValidationData, FAssetValidationReport& OutReport);

	static FAssetValidationReport GenerateReport(TArray<FAssetValidationData>& ValidationData);

	static void ToCSV(const FAssetValidationReport& ValidationData, FString& OutCSV);

	static FString ToCSV(const FAssetValidationReport& Report);

	static FString ToJSON(const FAssetValidationReport& Report);

	static void ToJSON(const FAssetValidationReport& Report, FString& OutCSV);

	static void ToLog(const FAssetValidationReport& Report, FString& OutLog);

	static FString ToLog(const FAssetValidationReport& Report);

	static bool SaveSmallReportToCSVFile(const FAssetValidationReport& Report);

	static bool SaveSmallReportToJSONFile(const FAssetValidationReport& Report);

	static bool StreamSmallReportToLog(const FAssetValidationReport& Report);

	static FString EnumResultToString(EValidationResult Result);

private:

	static void GenerateSummaryReportToCSV(const FValidationReportSummary& Summary, FString& OutCSV);

	static void GenerateFullReportToCSV(const TArray<FAssetValidationData>& ValidationData, FString& OutCSV);

	static void GenerateErrorsPerAssetToCSV(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutCSV);

	static void GenerateErrorsPerValidatorToCSV(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutCSV);
	
	static void GenerateSummaryReportToJSON(const FValidationReportSummary& Report, FString& OutJSON);

	static void GenerateFullReportToJSON(const TArray<FAssetValidationData>& ValidationData, FString& OutJSON);

	static void GenerateErrorsPerAssetToJSON(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutJSON);

	static void GenerateErrorsPerValidatorToJSON(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutJSON);

	static void GenerateSummaryReportToLog(const FValidationReportSummary& Report, FString& OutLog);

	static void GenerateFullReportToLog(const TArray<FAssetValidationData>& ValidationData, FString& OutLog);

	static void GenerateErrorsPerAssetToLog(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutLog);

	static void GenerateErrorsPerValidatorToLog(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutLog);

	static bool SaveStringAtomicallyToFile(const FString& Content, const FString& FilePath);
};