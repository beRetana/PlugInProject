#pragma once

namespace VerifierData
{
	static FString PASSED() { return TEXT("Passed"); }
	static FString INFORMATION() { return TEXT("Information"); }
	static FString WARNING() { return TEXT("Warning"); }
	static FString ERROR() { return TEXT("Error"); }
	static FString UNKNOWN() { return TEXT("Unknown"); }

	enum class EValidationResult : uint8
	{
		Passed_0 = 0,
		Information_1 = 1,
		Warning_2 = 2,
		Error_3 = 3,
		Size_4 = 4
	};

	static FString EnumResultToString(const EValidationResult& Result)
	{
		switch (Result)
		{
		case EValidationResult::Passed_0:
			return PASSED();
		case EValidationResult::Information_1:
			return INFORMATION();
		case EValidationResult::Warning_2:
			return WARNING();
		case EValidationResult::Error_3:
			return ERROR();
		default:
			return UNKNOWN();
		}
	}

	struct FAssetValidationData
	{
		const FAssetData* Asset;

		FString FixData;

		FString Message;

		FName ValidatorName;

		FName FixerName;

		EValidationResult Result;

		bool bCanAutoFix{ false };

		bool bSelectedFix{ false };

		FAssetValidationData() : Result(EValidationResult::Passed_0)
		{
		}

		FString ResultString() const
		{
			return EnumResultToString(Result);
		}
	};

	typedef TSharedPtr<FAssetValidationData> DataPtr;

	struct FValidationReportSummary
	{
		uint32 TotalAssets{ 0 };

		uint32 Passed{ 0 };

		uint32 Errors{ 0 };

		uint32 Warnings{ 0 };

		uint32 Information{ 0 };

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
		TArray<DataPtr> AllValidationData;

		TStaticArray<TArray<DataPtr>, static_cast<int32>(EValidationResult::Size_4)> ByResultValidationData;

		TArray<DataPtr>& operator[](EValidationResult Result)
		{
			const int32 StatusIndex = static_cast<int32>(Result);
			checkf(StatusIndex < static_cast<int32>(EValidationResult::Size_4), TEXT("Tried to fetch value but Index out of bounds"));
			return ByResultValidationData[StatusIndex];
		}

		void Add(FAssetValidationData& ValidationData)
		{
			const int32 StatusIndex = static_cast<int32>(ValidationData.Result);
			checkf(StatusIndex < static_cast<int32>(EValidationResult::Size_4), TEXT("Tried to add a value but Index out of bounds"));
			int32 DataIndex = AllValidationData.Add(MakeShared<FAssetValidationData>(ValidationData));
			ByResultValidationData[StatusIndex].Add(AllValidationData[DataIndex]);
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
			Assets.Reset();
		}

		FAssetValidationReport() = default;
	};
};

// This is to be used as a shortcut.
namespace VD = VerifierData;