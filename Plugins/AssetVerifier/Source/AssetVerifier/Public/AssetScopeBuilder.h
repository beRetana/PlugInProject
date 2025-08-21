
class IAssetRegistry; // Forward declaration since we are using it in the class declaration

class FAssetScopeBuilder
{
public:

	static TArray<FAssetData> BuildScopeAll(const FARFilter& Filter = FARFilter());
	static TArray<FAssetData> BuildScopeSelected(const FARFilter& Filter = FARFilter());
	static TArray<FAssetData> BuildScopeFolder(const FARFilter& Filter = FARFilter());

	static FARFilter MakeFilterScopeAll(const FARFilter& = FARFilter());
	static FARFilter MakeFilterScopeSelected(const FARFilter& = FARFilter());
	static FARFilter MakeFilterScopeFolders(const TArray<FName>& FoldersPaths, const FARFilter& = FARFilter());

	static void QueryAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssets);
	static TArray<FAssetData> QueryAssets(const FARFilter& Filter);

private:

	static IAssetRegistry& GetAssetRegistry();

	static inline const TCHAR* ASSET_REGISTRY_MODULE = TEXT("AssetRegistry");
	static inline const TCHAR* GAME_ROOT_PATH = TEXT("/Game");
	static inline const TCHAR* CONTENT_BROSER = TEXT("ContentBrowser");
};