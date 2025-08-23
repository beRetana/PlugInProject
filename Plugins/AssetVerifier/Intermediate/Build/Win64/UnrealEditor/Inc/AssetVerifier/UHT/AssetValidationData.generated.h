// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AssetValidationData.h"

#ifdef ASSETVERIFIER_AssetValidationData_generated_h
#error "AssetValidationData.generated.h already included, missing '#pragma once' in AssetValidationData.h"
#endif
#define ASSETVERIFIER_AssetValidationData_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FAssetValidationData **********************************************
#define FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h_17_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAssetValidationData_Statics; \
	static class UScriptStruct* StaticStruct();


struct FAssetValidationData;
// ********** End ScriptStruct FAssetValidationData ************************************************

// ********** Begin ScriptStruct FValidationReportSummary ******************************************
#define FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h_43_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FValidationReportSummary_Statics; \
	static class UScriptStruct* StaticStruct();


struct FValidationReportSummary;
// ********** End ScriptStruct FValidationReportSummary ********************************************

// ********** Begin ScriptStruct FAssetValidationReport ********************************************
#define FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h_66_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAssetValidationReport_Statics; \
	static class UScriptStruct* StaticStruct();


struct FAssetValidationReport;
// ********** End ScriptStruct FAssetValidationReport **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_breta_Downloads_Proyectos_Personales_Unreal_PlugInProject_Plugins_AssetVerifier_Source_AssetVerifier_Public_AssetValidationData_h

// ********** Begin Enum EValidationResult *********************************************************
#define FOREACH_ENUM_EVALIDATIONRESULT(op) \
	op(EValidationResult::Passed) \
	op(EValidationResult::Error) \
	op(EValidationResult::Warning) \
	op(EValidationResult::Information) 

enum class EValidationResult : uint8;
template<> struct TIsUEnumClass<EValidationResult> { enum { Value = true }; };
template<> ASSETVERIFIER_API UEnum* StaticEnum<EValidationResult>();
// ********** End Enum EValidationResult ***********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
