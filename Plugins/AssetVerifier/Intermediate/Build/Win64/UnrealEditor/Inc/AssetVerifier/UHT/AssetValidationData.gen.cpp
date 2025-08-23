// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AssetValidationData.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAssetValidationData() {}

// ********** Begin Cross Module References ********************************************************
ASSETVERIFIER_API UEnum* Z_Construct_UEnum_AssetVerifier_EValidationResult();
ASSETVERIFIER_API UScriptStruct* Z_Construct_UScriptStruct_FAssetValidationData();
ASSETVERIFIER_API UScriptStruct* Z_Construct_UScriptStruct_FAssetValidationReport();
ASSETVERIFIER_API UScriptStruct* Z_Construct_UScriptStruct_FValidationReportSummary();
UPackage* Z_Construct_UPackage__Script_AssetVerifier();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EValidationResult *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EValidationResult;
static UEnum* EValidationResult_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EValidationResult.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EValidationResult.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AssetVerifier_EValidationResult, (UObject*)Z_Construct_UPackage__Script_AssetVerifier(), TEXT("EValidationResult"));
	}
	return Z_Registration_Info_UEnum_EValidationResult.OuterSingleton;
}
template<> ASSETVERIFIER_API UEnum* StaticEnum<EValidationResult>()
{
	return EValidationResult_StaticEnum();
}
struct Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Error.DisplayName", "Error" },
		{ "Error.Name", "EValidationResult::Error" },
		{ "Information.DisplayName", "Information" },
		{ "Information.Name", "EValidationResult::Information" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
		{ "Passed.DisplayName", "Passed" },
		{ "Passed.Name", "EValidationResult::Passed" },
		{ "Warning.DisplayName", "Warning" },
		{ "Warning.Name", "EValidationResult::Warning" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EValidationResult::Passed", (int64)EValidationResult::Passed },
		{ "EValidationResult::Error", (int64)EValidationResult::Error },
		{ "EValidationResult::Warning", (int64)EValidationResult::Warning },
		{ "EValidationResult::Information", (int64)EValidationResult::Information },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AssetVerifier,
	nullptr,
	"EValidationResult",
	"EValidationResult",
	Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AssetVerifier_EValidationResult()
{
	if (!Z_Registration_Info_UEnum_EValidationResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EValidationResult.InnerSingleton, Z_Construct_UEnum_AssetVerifier_EValidationResult_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EValidationResult.InnerSingleton;
}
// ********** End Enum EValidationResult ***********************************************************

// ********** Begin ScriptStruct FAssetValidationData **********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FAssetValidationData;
class UScriptStruct* FAssetValidationData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FAssetValidationData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FAssetValidationData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAssetValidationData, (UObject*)Z_Construct_UPackage__Script_AssetVerifier(), TEXT("AssetValidationData"));
	}
	return Z_Registration_Info_UScriptStruct_FAssetValidationData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FAssetValidationData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetName_MetaData[] = {
		{ "Category", "Validation Data" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetPath_MetaData[] = {
		{ "Category", "Validation Data" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ValidatorName_MetaData[] = {
		{ "Category", "Validation Data" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[] = {
		{ "Category", "Validation Data" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "Category", "Validation Data" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_AssetName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetPath;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ValidatorName;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Result_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Result;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAssetValidationData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_AssetName = { "AssetName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationData, AssetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetName_MetaData), NewProp_AssetName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_AssetPath = { "AssetPath", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationData, AssetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetPath_MetaData), NewProp_AssetPath_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_ValidatorName = { "ValidatorName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationData, ValidatorName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ValidatorName_MetaData), NewProp_ValidatorName_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_Result_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationData, Result), Z_Construct_UEnum_AssetVerifier_EValidationResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Result_MetaData), NewProp_Result_MetaData) }; // 135418023
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationData, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAssetValidationData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_AssetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_AssetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_ValidatorName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_Result_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_Result,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetValidationData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAssetValidationData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AssetVerifier,
	nullptr,
	&NewStructOps,
	"AssetValidationData",
	Z_Construct_UScriptStruct_FAssetValidationData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetValidationData_Statics::PropPointers),
	sizeof(FAssetValidationData),
	alignof(FAssetValidationData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetValidationData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAssetValidationData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAssetValidationData()
{
	if (!Z_Registration_Info_UScriptStruct_FAssetValidationData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FAssetValidationData.InnerSingleton, Z_Construct_UScriptStruct_FAssetValidationData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FAssetValidationData.InnerSingleton;
}
// ********** End ScriptStruct FAssetValidationData ************************************************

// ********** Begin ScriptStruct FValidationReportSummary ******************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FValidationReportSummary;
class UScriptStruct* FValidationReportSummary::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FValidationReportSummary.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FValidationReportSummary.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FValidationReportSummary, (UObject*)Z_Construct_UPackage__Script_AssetVerifier(), TEXT("ValidationReportSummary"));
	}
	return Z_Registration_Info_UScriptStruct_FValidationReportSummary.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FValidationReportSummary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalAssets_MetaData[] = {
		{ "Category", "Validation Report Summary" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Passed_MetaData[] = {
		{ "Category", "Validation Report Summary" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Errors_MetaData[] = {
		{ "Category", "Validation Report Summary" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Warnings_MetaData[] = {
		{ "Category", "Validation Report Summary" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Information_MetaData[] = {
		{ "Category", "Validation Report Summary" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_TotalAssets;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Passed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Errors;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Warnings;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Information;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FValidationReportSummary>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_TotalAssets = { "TotalAssets", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FValidationReportSummary, TotalAssets), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalAssets_MetaData), NewProp_TotalAssets_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Passed = { "Passed", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FValidationReportSummary, Passed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Passed_MetaData), NewProp_Passed_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Errors = { "Errors", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FValidationReportSummary, Errors), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Errors_MetaData), NewProp_Errors_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Warnings = { "Warnings", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FValidationReportSummary, Warnings), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Warnings_MetaData), NewProp_Warnings_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Information = { "Information", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FValidationReportSummary, Information), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Information_MetaData), NewProp_Information_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FValidationReportSummary_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_TotalAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Passed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Errors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Warnings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewProp_Information,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FValidationReportSummary_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FValidationReportSummary_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AssetVerifier,
	nullptr,
	&NewStructOps,
	"ValidationReportSummary",
	Z_Construct_UScriptStruct_FValidationReportSummary_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FValidationReportSummary_Statics::PropPointers),
	sizeof(FValidationReportSummary),
	alignof(FValidationReportSummary),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FValidationReportSummary_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FValidationReportSummary_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FValidationReportSummary()
{
	if (!Z_Registration_Info_UScriptStruct_FValidationReportSummary.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FValidationReportSummary.InnerSingleton, Z_Construct_UScriptStruct_FValidationReportSummary_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FValidationReportSummary.InnerSingleton;
}
// ********** End ScriptStruct FValidationReportSummary ********************************************

// ********** Begin ScriptStruct FAssetValidationReport ********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FAssetValidationReport;
class UScriptStruct* FAssetValidationReport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FAssetValidationReport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FAssetValidationReport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAssetValidationReport, (UObject*)Z_Construct_UPackage__Script_AssetVerifier(), TEXT("AssetValidationReport"));
	}
	return Z_Registration_Info_UScriptStruct_FAssetValidationReport.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FAssetValidationReport_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ValidationData_MetaData[] = {
		{ "Category", "Asset Validation Report" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Summary_MetaData[] = {
		{ "Category", "Asset Validation Report" },
		{ "ModuleRelativePath", "Public/AssetValidationData.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ValidationData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ValidationData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Summary;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAssetValidationReport>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewProp_ValidationData_Inner = { "ValidationData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FAssetValidationData, METADATA_PARAMS(0, nullptr) }; // 1766014313
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewProp_ValidationData = { "ValidationData", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationReport, ValidationData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ValidationData_MetaData), NewProp_ValidationData_MetaData) }; // 1766014313
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewProp_Summary = { "Summary", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAssetValidationReport, Summary), Z_Construct_UScriptStruct_FValidationReportSummary, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Summary_MetaData), NewProp_Summary_MetaData) }; // 1092624473
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAssetValidationReport_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewProp_ValidationData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewProp_ValidationData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewProp_Summary,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetValidationReport_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAssetValidationReport_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AssetVerifier,
	nullptr,
	&NewStructOps,
	"AssetValidationReport",
	Z_Construct_UScriptStruct_FAssetValidationReport_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetValidationReport_Statics::PropPointers),
	sizeof(FAssetValidationReport),
	alignof(FAssetValidationReport),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetValidationReport_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAssetValidationReport_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAssetValidationReport()
{
	if (!Z_Registration_Info_UScriptStruct_FAssetValidationReport.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FAssetValidationReport.InnerSingleton, Z_Construct_UScriptStruct_FAssetValidationReport_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FAssetValidationReport.InnerSingleton;
}
// ********** End ScriptStruct FAssetValidationReport **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h__Script_AssetVerifier_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EValidationResult_StaticEnum, TEXT("EValidationResult"), &Z_Registration_Info_UEnum_EValidationResult, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 135418023U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FAssetValidationData::StaticStruct, Z_Construct_UScriptStruct_FAssetValidationData_Statics::NewStructOps, TEXT("AssetValidationData"), &Z_Registration_Info_UScriptStruct_FAssetValidationData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAssetValidationData), 1766014313U) },
		{ FValidationReportSummary::StaticStruct, Z_Construct_UScriptStruct_FValidationReportSummary_Statics::NewStructOps, TEXT("ValidationReportSummary"), &Z_Registration_Info_UScriptStruct_FValidationReportSummary, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FValidationReportSummary), 1092624473U) },
		{ FAssetValidationReport::StaticStruct, Z_Construct_UScriptStruct_FAssetValidationReport_Statics::NewStructOps, TEXT("AssetValidationReport"), &Z_Registration_Info_UScriptStruct_FAssetValidationReport, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAssetValidationReport), 1234650704U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h__Script_AssetVerifier_358167533(TEXT("/Script/AssetVerifier"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h__Script_AssetVerifier_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h__Script_AssetVerifier_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h__Script_AssetVerifier_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h__Script_AssetVerifier_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
