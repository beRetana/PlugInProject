
#include "AssetScopeBuilder.h"
#include "AssetRegistry\AssetRegistryModule.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

/// <summary>
/// Returns the asset registry module.
/// </summary>
/// <returns>IAssetRegistry&</returns>
IAssetRegistry& FAssetScopeBuilder::GetAssetRegistry()
{
	return FModuleManager::LoadModuleChecked<FAssetRegistryModule>(ASSET_REGISTRY_MODULE).Get();
}

/// <summary>
/// Returns a list of all assets in the game root path.
/// </summary>
/// <param name="Filter"></param>
/// <returns>FARFilter</returns>
FARFilter FAssetScopeBuilder::MakeFilterScopeAll()
{
	FARFilter Filter;
	Filter.PackagePaths.Add(GAME_ROOT_PATH);
	Filter.bRecursivePaths = true;
	return Filter;
}

/// <summary>
/// Returns a new filter that includes all assets inside the folder specified by the paths in the array.
/// </summary>
/// <param name="FoldersPaths"></param>
/// <param name="Filter"></param>
/// <returns>FARFilter</returns>
FARFilter FAssetScopeBuilder::MakeFilterScopeFolders(const TArray<FName>& FoldersPaths)
{
	FARFilter Filter;
	Filter.PackagePaths.Append(FoldersPaths);
	Filter.bRecursivePaths = true;
	return Filter;
}

/// <summary>
/// Returns a new filter that includes all assets in the selected folders and assets in the content browser.
/// </summary>
/// <param name="Filter"></param>
/// <returns>FARFilter</returns>
FARFilter FAssetScopeBuilder::MakeFilterScopeSelected()
{
	FARFilter Filter;
	Filter.bRecursivePaths = true;

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(CONTENT_BROSER);
	TArray<FString> SelectedPaths;
	ContentBrowserModule.Get().GetSelectedFolders(SelectedPaths);

	for (const FString& Path : SelectedPaths)
	{
		Filter.PackagePaths.Add(FName(*Path));
	}

	TArray<FAssetData> SelectedAssets;
	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

	for (const FAssetData& AssetPath : SelectedAssets)
	{
		Filter.SoftObjectPaths.Add(AssetPath.GetSoftObjectPath());
	}

	return Filter;
}

/// <summary>
/// Populates the array with all assets that match the filter.
/// </summary>
/// <param name="Filter"></param>
void FAssetScopeBuilder::QueryAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssets)
{
	OutAssets.Reset();
	GetAssetRegistry().GetAssets(Filter, OutAssets, false);
}

/// <summary>
/// Retuns an array of all assets that match the filter.
/// </summary>
/// <param name="Filter"></param>
/// <returns>TArray<FAssetData></returns>
TArray<FAssetData> FAssetScopeBuilder::QueryAssets(const FARFilter& Filter)
{
	TArray<FAssetData> Assets;
	GetAssetRegistry().GetAssets(Filter, Assets);
	return Assets;
}

/// <summary>
/// Returns a list of all assets in the game root path.
/// </summary>
/// <param name="Filter"></param>
/// <returns>TArray<FAssetData></returns>
TArray<FAssetData> FAssetScopeBuilder::BuildScopeAll()
{
	TArray<FAssetData> Assets;
	QueryAssets(MakeFilterScopeAll(), Assets);
	return Assets;
}

void FAssetScopeBuilder::BuildScopeAll(TArray<FAssetData>& OutAssets)
{
	QueryAssets(MakeFilterScopeAll(), OutAssets);
}

/// <summary>
/// Returns a list of all assets in the specified folders by the filter.
/// </summary>
/// <param name="Filter"></param>
/// <returns>TArray<FAssetData></returns>
TArray<FAssetData> FAssetScopeBuilder::BuildScopeFolder(const TArray<FName>& FoldersPaths)
{
	TArray<FAssetData> Assets;
	QueryAssets(MakeFilterScopeFolders(FoldersPaths), Assets);
	return Assets;
}

/// <summary>
/// Returns a list of all assets in the selected folders and assets in the content browser.
/// </summary>
/// <param name="Filter"></param>
/// <returns>TArray<FAssetData></returns>
TArray<FAssetData> FAssetScopeBuilder::BuildScopeSelected()
{
	TArray<FAssetData> Assets;
	QueryAssets(MakeFilterScopeSelected(), Assets);
	return Assets;
}