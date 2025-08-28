#pragma once

enum class EValidationResult : uint8
{
	Passed_0 = 0,
	Information_1 = 1,
	Warning_2 = 2,
	Error_3 = 3,
	Size_4 = 4
};

struct FAssetValidationData
{
	const FAssetData* Asset;

	FString FixData;

	FString Message;

	FName ValidatorName;

	FName FixerName;

	EValidationResult Result;

	bool bCanAutoFix{ false };

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

struct FFixerData
{
	TArray<FAssetValidationData> AllValidationData;

	TStaticArray<TArray<FAssetValidationData>, static_cast<int32>(EValidationResult::Size_4)> ByResultValidationData;

	TArray<FAssetValidationData>& operator[](EValidationResult Result)
	{
		const int32 StatusIndex = static_cast<int32>(Result);
		checkf(StatusIndex < static_cast<int32>(EValidationResult::Size_4), TEXT("Tried to fetch value but Index out of bounds"));
		return ByResultValidationData[StatusIndex];
	}

	void Add(FAssetValidationData& ValidationData)
	{
		const int32 StatusIndex = static_cast<int32>(ValidationData.Result);
		checkf(StatusIndex < static_cast<int32>(EValidationResult::Size_4), TEXT("Tried to add a value but Index out of bounds"));
		AllValidationData.Add(ValidationData);
		ByResultValidationData[StatusIndex].Add(ValidationData);
	}
};

struct FAssetValidationReport
{
	TMap<FName, FFixerData> ValidatorToFixerData;

	TMap<FName, int32> ErrorCountPerValidator;

	TMap<FName, int32> ErrorCountPerAsset;

	FValidationReportSummary Summary;

	TArray<FAssetData> Assets;

	void Add(const FName& FixerName, FAssetValidationData& Data)
	{
		ValidatorToFixerData.FindOrAdd(Data.ValidatorName).Add(Data);
	}

	void Reset()
	{
		ValidatorToFixerData.Reset();
		ErrorCountPerValidator.Reset();
		ErrorCountPerAsset.Reset();
		Summary.Reset();
	}

	FAssetValidationReport() = default;
};