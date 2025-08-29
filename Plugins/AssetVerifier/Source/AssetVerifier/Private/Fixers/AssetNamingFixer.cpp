#include "Fixers/AssetNamingFixer.h"
#include "AssetValidationData.h"
#include "AssetToolsModule.h"
#include "Utils/VerifierUtils.h"

void FAssetNamingFixer::Fix(FFixerData& FixerData)
{
	TArray<FAssetRenameData> AssetsToRename;
	AssetsToRename.Reserve(FixerData[EValidationResult::Error_3].Num());

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	for (const auto& ValidationData : FixerData[EValidationResult::Error_3])
	{
		UObject* Asset = ValidationData.Asset->GetAsset();
		if (Asset == nullptr) continue;

		const FString NewName{ ValidationData.FixData + TEXT("_") + ValidationData.Asset->AssetName.ToString() };
		const FString PackagePath{ ValidationData.Asset->PackagePath.ToString() / NewName};

		FString NewPath, NewAssetName;
		AssetTools.CreateUniqueAssetName(PackagePath, TEXT(""), NewPath, NewAssetName);

		AssetsToRename.Emplace(Asset, FPaths::GetPath(NewPath), NewAssetName);
	}

	if (AssetsToRename.Num() == 0) return;
	
	AssetTools.Get().RenameAssets(AssetsToRename);

	FVerifierUtils::CleanupRedirector(FixerData[EValidationResult::Error_3]);
}

FName FAssetNamingFixer::GetFixerName() const
{
	return FName(FIXER_NAME);
}