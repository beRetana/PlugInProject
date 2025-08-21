#pragma once

#include "CoreMinimal.h"

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
	FString AssetName;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FString ValidatorName;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	EValidationResult Result;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Data")
	FString Message;


	FAssetValidationData(const FString& InAssetName, const FString& InAssetPath, const FString& InValidatorName, EValidationResult InResult, const FString& InMessage)
		: AssetName(InAssetName)
		, AssetPath(InAssetPath)
		, ValidatorName(InValidatorName)
		, Result(InResult)
		, Message(InMessage)
	{}

	FAssetValidationData(){};
};

USTRUCT(BlueprintType)
struct ASSETVERIFIER_API FValidationReportSummary
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 TotalAssets;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Passed;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Errors;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Warnings;

	UPROPERTY(BlueprintReadOnly, Category = "Validation Report Summary")
	int32 Information;

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