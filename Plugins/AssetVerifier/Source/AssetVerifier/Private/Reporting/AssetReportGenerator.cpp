
#include "AssetReportGenerator.h"

void FAssetReportGenerator::GenerateReport(FAssetValidationReport& ReportOut)
{
	ReportOut.ErrorCountPerAsset.Empty();
	ReportOut.ErrorCountPerValidator.Empty();
	ReportOut.Summary.Reset();

	for (auto& groupData : ReportOut.ValidatorToFixerData)
	{
		for (auto& issueData : groupData.Value.AllValidationData)
		{
			if (!ReportOut.ErrorCountPerAsset.Contains(issueData.Asset->AssetName))
			{
				ReportOut.ErrorCountPerAsset.Add(issueData.Asset->AssetName, 0);
			}

			if (!ReportOut.ErrorCountPerValidator.Contains(issueData.ValidatorName))
			{
				ReportOut.ErrorCountPerValidator.Add(issueData.ValidatorName, 0);
			}

			switch (issueData.Result)
			{
			case EValidationResult::Passed_0:
				++ReportOut.Summary.Passed;
				break;
			case EValidationResult::Information_1:
				++ReportOut.Summary.Information;
				break;
			case EValidationResult::Warning_2:
				++ReportOut.Summary.Warnings;
				break;
			case EValidationResult::Error_3:
				++ReportOut.Summary.Errors;
				++ReportOut.ErrorCountPerAsset[issueData.Asset->AssetName];
				++ReportOut.ErrorCountPerValidator[issueData.ValidatorName];
				break;
			}
		}
	}
	
	ReportOut.Summary.TotalAssets = ReportOut.ErrorCountPerAsset.Num();
}

FAssetValidationReport FAssetReportGenerator::GenerateReport()
{
	FAssetValidationReport Report;
	GenerateReport(Report);
	return Report;
}

void FAssetReportGenerator::ToCSV(const FAssetValidationReport& ValidationReport, FString& OutCSV)
{
	OutCSV.Empty();

	GenerateSummaryReportToCSV(ValidationReport.Summary, OutCSV);
	OutCSV += TEXT("END\n");
	GenerateFullReportToCSV(ValidationReport.ValidatorToFixerData, OutCSV);
	OutCSV += TEXT("END\n");
	GenerateErrorsPerAssetToCSV(ValidationReport.ErrorCountPerAsset, OutCSV);
	OutCSV += TEXT("END\n");
	GenerateErrorsPerValidatorToCSV(ValidationReport.ErrorCountPerValidator, OutCSV);
	
}

void FAssetReportGenerator::GenerateSummaryReportToCSV(const FValidationReportSummary& Summary, FString& OutCSV)
{
	OutCSV += TEXT("Summary Stats, Count\n");
	OutCSV += FString::Printf(TEXT("Total Assets,%d\n"), Summary.TotalAssets);
	OutCSV += FString::Printf(TEXT("Total Errors,%d\n"), Summary.Errors);
	OutCSV += FString::Printf(TEXT("Total Warnings,%d\n"), Summary.Warnings);
	OutCSV += FString::Printf(TEXT("Total Information,%d\n"), Summary.Information);
	OutCSV += FString::Printf(TEXT("Total Passed,%d\n"), Summary.Passed);
}

void FAssetReportGenerator::GenerateFullReportToCSV(const TMap<FName, FFixerData>& ValidationData, FString& OutCSV)
{
	OutCSV += TEXT("Asset Name,Asset Path,Validator Name,Result,Message\n");

	for (const auto& DataGroup : ValidationData)
	{
		for (const auto& Data : DataGroup.Value.AllValidationData)
		{
			OutCSV += FString::Printf(TEXT("%s,%s,%s,%s,%s\n"),
				*Data.Asset->AssetName.ToString(),
				*Data.Asset->GetObjectPathString(),
				*Data.ValidatorName.ToString(),
				*Data.ResultString(),
				*Data.Message);
		}
	}
}

void FAssetReportGenerator::GenerateErrorsPerAssetToCSV(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutCSV)
{
	OutCSV += TEXT("Asset Name,Error Count\n");
	for (const auto& AssetError : ErrorCountPerAsset)
	{
		OutCSV += FString::Printf(TEXT("%s,%d\n"), *AssetError.Key.ToString(), AssetError.Value);
	}
}

void FAssetReportGenerator::GenerateErrorsPerValidatorToCSV(const TMap<FName, int32>& ErrorCountPerValidator, FString& OutCSV)
{
	OutCSV += TEXT("Validator Name,Error Count\n");
	for (const auto& ValidatorError : ErrorCountPerValidator)
	{
		OutCSV += FString::Printf(TEXT("%s,%d\n"), *ValidatorError.Key.ToString(), ValidatorError.Value);
	}
}

FString FAssetReportGenerator::ToCSV(const FAssetValidationReport& ValidationReport)
{
	FString CSV;
	ToCSV(ValidationReport, CSV);
	return CSV;
}

void FAssetReportGenerator::ToJSON(const FAssetValidationReport& Report, FString& OutJSON)
{
	OutJSON.Empty();
	
	OutJSON += TEXT("{\n");					   // Start of JSON

	GenerateSummaryReportToJSON(Report.Summary, OutJSON); // Add Summary Report

	OutJSON += TEXT(",\n");

	GenerateErrorsPerAssetToJSON(Report.ErrorCountPerAsset, OutJSON); // Add Errors Per Asset

	OutJSON += TEXT(",\n");

	GenerateErrorsPerValidatorToJSON(Report.ErrorCountPerValidator, OutJSON); // Add Errors Per Validator

	OutJSON += TEXT(",\n");

	GenerateFullReportToJSON(Report.ValidatorToFixerData, OutJSON); // Add Full Report

	OutJSON += TEXT("}\n");					   // End of JSON
}

void FAssetReportGenerator::GenerateSummaryReportToJSON(const FValidationReportSummary& Summary, FString& OutJSON)
{
	OutJSON += TEXT("\t\"SummaryReport\":\n"); 
	OutJSON += TEXT("\t{\n");
	OutJSON += FString::Printf(TEXT("\t\t\"TotalAssets\": %d,\n"), Summary.TotalAssets);
	OutJSON += FString::Printf(TEXT("\t\t\"TotalPassed\": %d,\n"), Summary.Passed);
	OutJSON += FString::Printf(TEXT("\t\t\"TotalErrors\": %d,\n"), Summary.Errors);
	OutJSON += FString::Printf(TEXT("\t\t\"TotalWarnings\": %d,\n"), Summary.Warnings);
	OutJSON += FString::Printf(TEXT("\t\t\"TotalInformation\": %d\n"), Summary.Information);
	OutJSON += TEXT("\t}");
}

void FAssetReportGenerator::GenerateFullReportToJSON(const TMap<FName, FFixerData>& ValidationData, FString& OutJSON)
{
	OutJSON += TEXT("\t\"FullReport\":\n");
	OutJSON += TEXT("\t\t[\n");

	int32 FixerIndex{0};
	for (const auto& Fixer : ValidationData)
	{
		int32 AssetDataIndex{0};

		for (const auto& AssetData : Fixer.Value.AllValidationData)
		{
			OutJSON += TEXT("\t\t\t{\n");
			OutJSON += FString::Printf(TEXT("\t\t\t\t\"AssetName\": \"%s\",\n"), *AssetData.Asset->AssetName.ToString());
			OutJSON += FString::Printf(TEXT("\t\t\t\t\"AssetPath\": \"%s\",\n"), *AssetData.Asset->GetObjectPathString());
			OutJSON += FString::Printf(TEXT("\t\t\t\t\"ValidatorName\": \"%s\",\n"), *AssetData.ValidatorName.ToString());
			OutJSON += FString::Printf(TEXT("\t\t\t\t\"Result\": \"%s\",\n"), *AssetData.ResultString());
			OutJSON += FString::Printf(TEXT("\t\t\t\t\"Message\": \"%s\"\n"), *AssetData.Message);

			OutJSON += (AssetDataIndex < Fixer.Value.AllValidationData.Num() - 1 && FixerIndex < ValidationData.Num() - 1) ? TEXT("\t\t\t},\n") : TEXT("\t\t\t}\n");
			++AssetDataIndex;
		}
		++FixerIndex;
	}

	OutJSON += TEXT("\t\t]");
}

void FAssetReportGenerator::GenerateErrorsPerAssetToJSON(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutJSON)
{
	OutJSON += TEXT("\t\"ErrorsPerAsset\":\n");// Start of ErrorsPerAsset
	OutJSON += TEXT("\t\t[\n");
	int32 objectCount = 0;

	for (const auto& AssetError : ErrorCountPerAsset)
	{
		OutJSON += TEXT("\t\t\t{\n");
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"AssetName\": \"%s\",\n"), *AssetError.Key.ToString());
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"ErrorCount\": %d\n"), AssetError.Value);

		OutJSON += (objectCount < ErrorCountPerAsset.Num() - 1) ? TEXT("\t\t\t},\n") : TEXT("\t\t\t}\n");

		++objectCount;
	}

	OutJSON += TEXT("\t\t]");
}

void FAssetReportGenerator::GenerateErrorsPerValidatorToJSON(const TMap<FName, int32>& ErrorCountPerValidator, FString& OutJSON)
{
	OutJSON += TEXT("\t\"ErrorsPerValidator\":\n"); // Start of ErrorsPerValidator
	OutJSON += TEXT("\t\t[\n");
	int32 objectCount = 0;

	for (const auto& ValidatorError : ErrorCountPerValidator)
	{
		OutJSON += TEXT("\t\t\t{\n");
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"ValidatorName\": \"%s\", \n"), *ValidatorError.Key.ToString());
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"ErrorCount\": %d\n"), ValidatorError.Value);

		OutJSON += (objectCount < ErrorCountPerValidator.Num() - 1) ? TEXT("\t\t\t},\n") : TEXT("\t\t\t}\n");

		++objectCount;
	}
	OutJSON += TEXT("\t\t]");
}

FString FAssetReportGenerator::ToJSON(const FAssetValidationReport& Report)
{
	FString JSON;
	ToJSON(Report, JSON);
	return JSON;
}

void FAssetReportGenerator::ToLog(const FAssetValidationReport& Report, FString& OutLog)
{
	OutLog += TEXT(" \n============= Asset Validation Report =============\n\n");
	GenerateSummaryReportToLog(Report.Summary, OutLog);
	GenerateErrorsPerValidatorToLog(Report.ErrorCountPerValidator, OutLog);
	GenerateErrorsPerAssetToLog(Report.ErrorCountPerAsset, OutLog);
	GenerateFullReportToLog(Report.ValidatorToFixerData, OutLog);
	OutLog += TEXT(" \n===================================================\n");
}

void FAssetReportGenerator::GenerateSummaryReportToLog(const FValidationReportSummary& Summary, FString& OutLog)
{
	OutLog += TEXT(" \n--------------------Summary------------------------\n\n");
	OutLog += FString::Printf(TEXT("Total Assets: %d\n"), Summary.TotalAssets);
	OutLog += FString::Printf(TEXT("Total Passed: %d\n"), Summary.Passed);
	OutLog += FString::Printf(TEXT("Total Errors: %d\n"), Summary.Errors);
	OutLog += FString::Printf(TEXT("Total Warnings: %d\n"), Summary.Warnings);
	OutLog += FString::Printf(TEXT("Total Information: %d\n\n"), Summary.Information);
}

void FAssetReportGenerator::GenerateFullReportToLog(const TMap<FName, FFixerData>& ValidationData, FString& OutLog)
{
	OutLog += TEXT(" \n------------------Full Report----------------------\n\n");
	for (const auto& DataGroup : ValidationData)
	{
		for (const auto& Row : DataGroup.Value.AllValidationData)
		{
			OutLog += FString::Printf(TEXT("[%s] | %s | %s |\n"),
				*Row.ResultString(),
				*Row.Asset->AssetName.ToString(),
				*Row.ValidatorName.ToString());
			OutLog += FString::Printf(TEXT("Asset Path: %s\n"), *Row.Asset->GetObjectPathString());
			OutLog += FString::Printf(TEXT("Message: %s\n"), *Row.Message);
			OutLog += TEXT("---------------------------------------------------\n");
		}
	}
}

void FAssetReportGenerator::GenerateErrorsPerAssetToLog(const TMap<FName, int32>& ErrorCountPerAsset, FString& OutLog)
{
	OutLog += TEXT(" \n---------------Errors Per Asset--------------------\n\n");
	for (const auto& AssetError : ErrorCountPerAsset)
	{
		OutLog += FString::Printf(TEXT("Asset: %s | Error Count: %d\n"), *AssetError.Key.ToString(), AssetError.Value);
	}
}

void FAssetReportGenerator::GenerateErrorsPerValidatorToLog(const TMap<FName, int32>& ErrorCountPerValidator, FString& OutLog)
{
	OutLog += TEXT(" \n-------------Errors Per Validator------------------\n\n");
	for (const auto& ValidatorError : ErrorCountPerValidator)
	{
		OutLog += FString::Printf(TEXT("Validator: %s | Error Count: %d\n"), *ValidatorError.Key.ToString(), ValidatorError.Value);
	}
}

FString FAssetReportGenerator::ToLog(const FAssetValidationReport& Report)
{
	FString Log;
	ToLog(Report, Log);
	return Log;
}

bool FAssetReportGenerator::StreamSmallReportToLog(const FAssetValidationReport& Report)
{
	FString Log;
	ToLog(Report, Log);
	UE_LOG(LogTemp, Log, TEXT("%s"), *Log);
	return true;
}

bool FAssetReportGenerator::SaveSmallReportToCSVFile(const FAssetValidationReport& Report)
{
	FString Directory = FPaths::ProjectSavedDir() / TEXT("Reports/CSVs");

	if (!IFileManager::Get().MakeDirectory(*Directory, true))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *Directory);
		return false;
	}

	FString CSV;
	GenerateSummaryReportToCSV(Report.Summary, CSV);
	if (!SaveStringAtomicallyToFile(CSV, Directory / TEXT("Summary.csv")))
		return false;
	CSV.Empty();

	GenerateFullReportToCSV(Report.ValidatorToFixerData, CSV);
	if (!SaveStringAtomicallyToFile(CSV, Directory / TEXT("FullReport.csv")))
		return false;
	CSV.Empty();

	GenerateErrorsPerAssetToCSV(Report.ErrorCountPerValidator, CSV);
	if (!SaveStringAtomicallyToFile(CSV, Directory / TEXT("ErrorsPerAsset.csv")))
		return false;
	CSV.Empty();

	GenerateErrorsPerValidatorToCSV(Report.ErrorCountPerAsset, CSV);
	if (!SaveStringAtomicallyToFile(CSV, Directory / TEXT("ErrorsPerValidator.csv")))
		return false;

	return true;
}

bool FAssetReportGenerator::SaveStringAtomicallyToFile(const FString& Content, const FString& FilePath)
{
	const FString Dir = FPaths::GetPath(*FilePath);
	const FString TempFilePath = Dir / (FPaths::GetBaseFilename(FilePath) + TEXT(".part"));

	if (!FFileHelper::SaveStringToFile(Content, *TempFilePath, FFileHelper::EEncodingOptions::ForceUTF8, &IFileManager::Get(), 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to write to temporary file: %s"), *TempFilePath);
		return false;
	}

	if (!IFileManager::Get().Move(*FilePath, *TempFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to move temporary file to final destination: %s"), *FilePath);
		IFileManager::Get().Delete(*TempFilePath);
		return false;
	}

	return true;
}

bool FAssetReportGenerator::SaveSmallReportToJSONFile(const FAssetValidationReport& Report)
{
	FString Directory = FPaths::ProjectSavedDir() / TEXT("Reports/JSONs");

	if (!IFileManager::Get().MakeDirectory(*Directory, true))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *Directory);
		return false;
	}

	FString JSON;
	ToJSON(Report, JSON);
	return SaveStringAtomicallyToFile(JSON, Directory / TEXT("ValidationReport.json"));
}
