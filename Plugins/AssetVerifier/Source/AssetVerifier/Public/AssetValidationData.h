#pragma once

enum class EValidationResult : uint8
{
	Passed_0		= 0,
	Information_1	= 1,
	Warning_2		= 2,
	Error_3			= 3,
};

struct FAssetValidationData
{
	FAssetData Asset;

	FName ValidatorName;

	FName FixerName;

	EValidationResult Result;

	FString Message;

	FAssetValidationData() : Result(EValidationResult::Passed_0)
	{
	}
};

struct FValidationReportSummary
{
	uint32 TotalAssets{0};

	uint32 Passed{0};

	uint32 Errors{0};

	uint32 Warnings{0};

	uint32 Information{0};

	void Reset()
	{
		TotalAssets = 0;
		Passed = 0;
		Errors = 0;
		Warnings = 0;
		Information = 0;
	}

	FValidationReportSummary() = default;
};

struct FAssetValidationReport
{
	TArray<TArray<FAssetValidationData>> ValidationData;

	FValidationReportSummary Summary;

	TMap<FName, int32> ErrorCountPerValidator;

	TMap<FName, int32> ErrorCountPerAsset;

	FAssetValidationReport() = default;
};