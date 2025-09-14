#include "Fixers/AssetNamingFixer.h"
#include "AssetValidationData.h"
#include "AssetToolsModule.h"
#include "Utils/VerifierUtils.h"

void FAssetNamingFixer::Fix(VD::FFixerData& FixerData)
{
	TArray<FAssetRenameData> AssetsToRename;
	AssetsToRename.Reserve(FixerData[VD::EValidationResult::Error_3].Num());

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	for (auto ValidationData : FixerData[VD::EValidationResult::Error_3])
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), ValidationData->bSelectedFix ? TEXT("PROCESS") : TEXT("SKIP"));
		if (!ValidationData->bSelectedFix) continue;

		UObject* Asset = ValidationData->Asset->GetAsset();
		if (Asset == nullptr) continue;

		const FString NewName{ ValidationData->FixData + ValidationData->Asset->AssetName.ToString() };
		const FString PackagePath{ ValidationData->Asset->PackagePath.ToString() / NewName};

		FString NewPath, NewAssetName;
		AssetTools.CreateUniqueAssetName(PackagePath, TEXT(""), NewPath, NewAssetName);

		AssetsToRename.Emplace(Asset, FPaths::GetPath(NewPath), NewAssetName);
		ValidationData->bCanAutoFix = true;
	}

	if (AssetsToRename.Num() == 0) return;
	
	AssetTools.Get().RenameAssets(AssetsToRename);

	FVerifierUtils::CleanupRedirector(FixerData[VD::EValidationResult::Error_3]);
}

FName FAssetNamingFixer::GetFixerName() const
{
	return FixerName;
}