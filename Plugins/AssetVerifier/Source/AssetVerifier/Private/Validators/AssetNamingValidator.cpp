
#include "Validators/AssetNamingValidator.h"	
#include "AssetVerifierSettings.h"
#include "AssetValidationData.h"

#define LOCTEXT_NAMESPACE "AssetNamingValidator"

const TCHAR* FAssetNamingValidator::ASSET_REGISTRY = TEXT("AssetRegistry");

void FAssetNamingValidator::Validate(const TArray<FAssetData>& Assets, TArray<TArray<FAssetValidationData>>& OutValidationData)
{
	UE_LOG(LogTemp, Log, TEXT("Checking For Naming Convention On Static Meshes: %s"), *NameConventionPrefix);
	
	FString StaticClassName = UStaticMesh::StaticClass()->GetClassPathName().ToString();

	InvalidAssetsNum = 0;
	CheckedAssetsNum = 0;

	for (const FAssetData& asset : Assets)
	{
		if (!asset.IsTopLevelAsset() || asset.AssetClassPath.ToString() != StaticClassName) continue;
		FAssetValidationData ValidationData;
		FillValidationData(ValidationData, asset);
		OutValidationData[static_cast<int32>(ValidationData.Result)].Emplace(MoveTemp(ValidationData));
	}

	if (InvalidAssetsNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d Assets do not follow naming convention"), InvalidAssetsNum);
	}

	UE_LOG(LogTemp, Log, TEXT("%d Static Meshes were checked"), CheckedAssetsNum);
}

void FAssetNamingValidator::FillValidationData(FAssetValidationData& OutValidationData, const FAssetData& Asset)
{
	OutValidationData.Asset = Asset;
	OutValidationData.ValidatorName = GetValidatorName();
	++CheckedAssetsNum;

	FString AssetNameStr = Asset.AssetName.ToString();

	if (AssetNameStr.StartsWith(NameConventionPrefix))
	{
		OutValidationData.Result = EValidationResult::Passed_0;
		OutValidationData.Message = FString::Printf(
			TEXT("Asset %s follows naming convention: %s"),
			*AssetNameStr,
			*NameConventionPrefix);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Asset %s does not follow naming convention: %s"), 
			*AssetNameStr,
			*NameConventionPrefix);
		
		++InvalidAssetsNum;
		OutValidationData.Result = EValidationResult::Error_3;
		OutValidationData.Message = FString::Printf(
			TEXT("Asset %s does not follow the naming convention: %s"), 
			*AssetNameStr,
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

FName FAssetNamingValidator::GetValidatorName() const
{
	return FName(VALIDATOR_NAME);
}

#undef LOCTEXT_NAMESPACE