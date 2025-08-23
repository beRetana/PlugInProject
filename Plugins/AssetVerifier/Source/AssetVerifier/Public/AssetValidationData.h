#pragma once

#include "AssetValidationData.generated.h"

UENUM(BlueprintType)
enum class EValidationResult : uint8
{
	Passed			UMETA(DisplayName = "Passed"),
	Error			UMETA(DisplayName = "Error"),
	Warning			UMETA(DisplayName = "Warning"),
	Information		UMETA(DisplayName = "Information")
};

USTRUCT(BlueprintType)
struct ASSETVERIFIER_API FAssetValidationData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FName AssetName;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FName ValidatorName;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	EValidationResult Result;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FString Message;


	FAssetValidationData() : Result(EValidationResult::Passed)
	{
	}
};

USTRUCT(BlueprintType)
struct ASSETVERIFIER_API FValidationReportSummary
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 TotalAssets{0};

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Passed{0};

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Errors{0};

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Warnings{0};

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Information{0};

	FValidationReportSummary() = default;
};

USTRUCT(BlueprintType)
struct ASSETVERIFIER_API FAssetValidationReport
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Asset Validation Report")
	TArray<FAssetValidationData> ValidationData;

	UPROPERTY(BlueprintReadOnly, Category = "Asset Validation Report")
	FValidationReportSummary Summary;

	TMap<FName, int32> ErrorCountPerValidator;
	TMap<FName, int32> ErrorCountPerAsset;

	FAssetValidationReport() = default;
};