#include "Utils/VerifierUtils.h"
#include "AssetValidationData.h"
#include "AssetRegistry/AssetData.h"
#include "SourceControlHelpers.h"
#include "AssetToolsModule.h"

void FVerifierUtils::CleanupRedirector(const TArray<FAssetValidationData>& ValidationData)
{
	TSet<UObjectRedirector*> RedirectorsToFix;

	const FTopLevelAssetPath RedirectorClassPath = UObjectRedirector::StaticClass()->GetClassPathName();

	for (const auto& AssetData: ValidationData)
	{
		if (!AssetData.Asset->IsValid()) continue;

		if (AssetData.Asset->AssetClassPath != RedirectorClassPath) continue;

		if (UObject* Asset = AssetData.Asset->GetAsset())
		{
			if (auto* Redirector = Cast<UObjectRedirector>(Asset))
			{
				RedirectorsToFix.Add(Redirector);
			}
		}
	}

	if (RedirectorsToFix.Num() <= 0) return;
	
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().FixupReferencers(RedirectorsToFix.Array());
}

void FVerifierUtils::SaveDirtyAssets(const TArray<FAssetData>& ValidationData)
{
	TSet<UPackage*> AssetsToSave;
	AssetsToSave.Reserve(ValidationData.Num());

	for (const FAssetData& AssetData: ValidationData)
	{
		if (!AssetData.IsValid()) continue;
		
		if (UPackage* Package = FindPackage(nullptr, *AssetData.PackageName.ToString()))
		{
			AssetsToSave.Add(Package);
		}
	}

	if (AssetsToSave.Num() <= 0) return;

	TArray<UPackage*> DirtyPackages = AssetsToSave.Array();
	CheckoutInSourceControl(DirtyPackages);
	const bool bChangesSaved = UEditorLoadingAndSavingUtils::SavePackages(DirtyPackages, true);
	UE_LOG(LogTemp, Log, TEXT("Tried to save %d packages (dirty-only). Result: %s"),
		AssetsToSave.Num(),
		bChangesSaved ? TEXT("Success/All OK") : TEXT("Partial or Failed"));
}

bool FVerifierUtils::CheckoutInSourceControl(const TArray<UPackage*>& Packages)
{
	if (!USourceControlHelpers::IsEnabled() || !USourceControlHelpers::IsAvailable()) return true;

	TArray<FString> FileRoutes = USourceControlHelpers::PackageFilenames(Packages);
	FileRoutes.RemoveAll([](const FString& FileRoute) { return FileRoute.IsEmpty(); });

	if (FileRoutes.Num() <= 0) return true;

	TArray<UPackage*> FailedPackages;

	const bool bCheckDirty = true;
	const bool bPromptToSave = true;
	const bool bAlreadyCheckedOut = false;
	const bool bCanBeDeclined = true;

	const auto Result = FEditorFileUtils::PromptForCheckoutAndSave(
		Packages,
		bCheckDirty,
		bPromptToSave, 
		&FailedPackages, 
		bAlreadyCheckedOut, 
		bCanBeDeclined);

	const bool bSuccess = Result == FEditorFileUtils::EPromptReturnCode::PR_Success && FailedPackages.Num() == 0;
	
	UE_LOG(LogTemp, Log, TEXT("Tried to check out/add %d files in source control. Result: %s"),
		FileRoutes.Num(),
		bSuccess ? TEXT("Success/All OK") : TEXT("Partial or Failed"));
	
	return bSuccess;
}