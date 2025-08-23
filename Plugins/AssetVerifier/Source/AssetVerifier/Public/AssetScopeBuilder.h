#pragma once

class IAssetRegistry; // Forward declaration since we are using it in the class declaration

class FAssetScopeBuilder
{
public:

	static TArray<FAssetData> BuildScopeAll();
	static TArray<FAssetData> BuildScopeSelected();
	static TArray<FAssetData> BuildScopeFolder(const TArray<FName>& FoldersPaths);

	static FARFilter MakeFilterScopeAll();
	static FARFilter MakeFilterScopeSelected();
	static FARFilter MakeFilterScopeFolders(const TArray<FName>& FoldersPaths);

	static void QueryAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssets);
	static TArray<FAssetData> QueryAssets(const FARFilter& Filter);

private:

	static IAssetRegistry& GetAssetRegistry();

	static inline const TCHAR* ASSET_REGISTRY_MODULE = TEXT("AssetRegistry");
	static inline const TCHAR* GAME_ROOT_PATH = TEXT("/Game");
	static inline const TCHAR* CONTENT_BROSER = TEXT("ContentBrowser");
};