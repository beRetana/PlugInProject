
#include "AssetReportGenerator.h"

void FAssetReportGenerator::GenerateReport(const TArray<FAssetValidationData>& ValidationData, FAssetValidationReport& ReportOut)
{
	ReportOut.ValidationData = ValidationData;
	ReportOut.ErrorCountPerAsset.Empty();
	ReportOut.ErrorCountPerValidator.Empty();

	for (auto issueData : ValidationData)
	{
		if (!ReportOut.ErrorCountPerAsset.Contains(issueData.AssetName))
		{
			ReportOut.ErrorCountPerAsset.Add(issueData.AssetName, 0);
		}

		if (!ReportOut.ErrorCountPerValidator.Contains(issueData.ValidatorName))
		{
			ReportOut.ErrorCountPerValidator.Add(issueData.ValidatorName, 0);
		}

		switch (issueData.Result)
		{
			case EValidationResult::Passed:
				++ReportOut.Summary.Passed;
				break;
			case EValidationResult::Information:
				++ReportOut.Summary.Information;
				break;
			case EValidationResult::Warning:
				++ReportOut.Summary.Warnings;
				break;
			case EValidationResult::Error:
				++ReportOut.Summary.Errors;
				++ReportOut.ErrorCountPerAsset[issueData.AssetName];
				++ReportOut.ErrorCountPerValidator[issueData.ValidatorName];
				break;
		}
	}

	ReportOut.Summary.TotalAssets = ReportOut.ErrorCountPerAsset.Num();
}

FAssetValidationReport FAssetReportGenerator::GenerateReport(const TArray<FAssetValidationData>& ValidationData)
{
	FAssetValidationReport Report;
	GenerateReport(ValidationData, Report);
	return Report;
}

void FAssetReportGenerator::ToCSV(const FAssetValidationReport& ValidationReport, FString& OutCSV)
{
	OutCSV.Empty();

	GenerateSummaryReportToCSV(ValidationReport.Summary, OutCSV);
	OutCSV += TEXT("END\n");
	GenerateFullReportToCSV(ValidationReport.ValidationData, OutCSV);
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

void FAssetReportGenerator::GenerateFullReportToCSV(const TArray<FAssetValidationData>& ValidationData, FString& OutCSV)
{
	OutCSV += TEXT("Asset Name,Asset Path,Validator Name,Result,Message\n");
	for (const auto& Data : ValidationData)
	{
		OutCSV += FString::Printf(TEXT("%s,%s,%s,%s,%s\n"),
			*Data.AssetName.ToString(),
			*Data.AssetPath,
			*Data.ValidatorName.ToString(),
			*UEnum::GetValueAsString(Data.Result),
			*Data.Message);
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

	GenerateFullReportToJSON(Report.ValidationData, OutJSON); // Add Full Report

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

void FAssetReportGenerator::GenerateFullReportToJSON(const TArray<FAssetValidationData>& ValidationData, FString& OutJSON)
{
	OutJSON += TEXT("\t\"FullReport\":\n");
	OutJSON += TEXT("\t\t[\n");

	for (int index = 0; index < ValidationData.Num(); ++index)
	{
		const auto& row = ValidationData[index];
		OutJSON += TEXT("\t\t\t{\n");
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"AssetName\": \"%s\",\n"), *row.AssetName.ToString());
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"AssetPath\": \"%s\",\n"), *row.AssetPath);
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"ValidatorName\": \"%s\",\n"), *row.ValidatorName.ToString());
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"Result\": \"%s\",\n"), *UEnum::GetValueAsString(row.Result));
		OutJSON += FString::Printf(TEXT("\t\t\t\t\"Message\": \"%s\"\n"), *row.Message);

		OutJSON += (index < ValidationData.Num() - 1) ? TEXT("\t\t\t},\n") : TEXT("\t\t\t}\n");
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
	GenerateFullReportToLog(Report.ValidationData, OutLog);
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

void FAssetReportGenerator::GenerateFullReportToLog(const TArray<FAssetValidationData>& ValidationData, FString& OutLog)
{
	OutLog += TEXT(" \n------------------Full Report----------------------\n\n");
	for (const auto& Data : ValidationData)
	{
		FString ResultString;
		
		switch (Data.Result)
		{
			case EValidationResult::Passed:
				ResultString = TEXT("Passed");
				break;
			case EValidationResult::Information:
				ResultString = TEXT("Information");
				break;
			case EValidationResult::Warning:
				ResultString = TEXT("Warning");
				break;
			case EValidationResult::Error:
				ResultString = TEXT("Error");
				break;
		}

		OutLog += FString::Printf(TEXT("[%s] | %s | %s |\n"),
			*ResultString,
			*Data.AssetName.ToString(),
			*Data.ValidatorName.ToString());
		OutLog += FString::Printf(TEXT("Asset Path: %s\n"), *Data.AssetPath);
		OutLog += FString::Printf(TEXT("Message: %s\n"), *Data.Message);
		OutLog += TEXT("---------------------------------------------------\n");
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

bool FAssetReportGenerator::SaveSmallReportToCSVFile(const FAssetValidationReport& Report)
{
	FString Directory = FPaths::ProjectSavedDir() / TEXT("Reports");

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

	GenerateFullReportToCSV(Report.ValidationData, CSV);
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

bool FAssetReportGenerator::SaveReportToJSONFile(const FAssetValidationReport& Report, const FString& FilePath)
{
	FString JSON;
	ToJSON(Report, JSON);
	return FFileHelper::SaveStringToFile(JSON, *FilePath);
}
