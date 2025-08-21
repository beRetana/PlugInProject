
#include "Validators/AssetNamingValidator.h"	
#include "AssetVerifierSettings.h"
#include "AssetValidationData.h"
#include "AssetScopeBuilder.h"

#define LOCTEXT_NAMESPACE "AssetNamingValidator"

const TCHAR* FAssetNamingValidator::ASSET_REGISTRY = TEXT("AssetRegistry");

void FAssetNamingValidator::Validate(TArray<FAssetData>& Assets, TArray<FAssetValidationData>& OutValidationData)
{
	UE_LOG(LogTemp, Log, TEXT("Checking For Naming Convention On Static Meshes: %s"), *NameConventionPrefix);
	
	FARFilter Filter = FARFilter();
	Filter.ClassPaths.Empty();
	Filter.ClassPaths.Add(UStaticMesh::StaticClass()->GetClassPathName());
	FAssetScopeBuilder::QueryAssets(Filter, Assets);

	InvalidAssetsNum = 0;
	CheckedAssetsNum = 0;

	for (const FAssetData& asset : Assets)
	{
		FAssetValidationData ValidationData;
		FillValidationData(ValidationData, asset);
		OutValidationData.Add(ValidationData);
	}

	if (InvalidAssetsNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d Assets do not follow naming convention"), InvalidAssetsNum);
	}

	UE_LOG(LogTemp, Log, TEXT("%d Static Meshes were checked"), CheckedAssetsNum);
}

void FAssetNamingValidator::FillValidationData(FAssetValidationData& OutValidationData, const FAssetData& Asset)
{
	OutValidationData.AssetName = Asset.AssetName.ToString();
	OutValidationData.AssetPath = Asset.GetObjectPathString();
	OutValidationData.ValidatorName = GetValidatorName();
	++CheckedAssetsNum;

	if (OutValidationData.AssetName.StartsWith(NameConventionPrefix))
	{
		OutValidationData.Result = EValidationResult::Passed;
		OutValidationData.Message = FString::Printf(
			TEXT("Asset %s follows naming convention: %s"),
			*OutValidationData.AssetName, 
			*NameConventionPrefix);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Asset %s does not follow naming convention: %s"), 
			*OutValidationData.AssetName,
			*NameConventionPrefix);
		
		++InvalidAssetsNum;
		OutValidationData.Result = EValidationResult::Error;
		OutValidationData.Message = FString::Printf(
			TEXT("Asset %s does not follow the naming convention: %s"), 
			*OutValidationData.AssetName, 
			*NameConventionPrefix);
	}
}

void FAssetNamingValidator::ApplySettings(const FAssetVerifierSettings& Settings)
{
	NameConventionPrefix = Settings.StaticMeshPrefixValue;
	UE_LOG(LogTemp, Log, TEXT("Loaded Naming Convention: %s"), *NameConventionPrefix);
}

FString FAssetNamingValidator::GetConvention() const
{
	return NameConventionPrefix;
}

void FAssetNamingValidator::ChangeConvention(const FString& NewConvention)
{
	NameConventionPrefix = NewConvention;
}

FString FAssetNamingValidator::GetValidatorName() const
{
	return FString(VALIDATOR_NAME);
}

#undef LOCTEXT_NAMESPACE