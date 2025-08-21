#pragma once

#include "Misc/ConfigCacheIni.h"
#include <Delegates/DelegateCombinations.h>

class FAssetVerifierSettings
{
public:

	FString StaticMeshPrefixValue;

	void LoadSettings();
	void SaveSettings() const;

	DECLARE_MULTICAST_DELEGATE(FOnSettingsChanged);

	FOnSettingsChanged OnSettingsChanged;
	
private:

	const TCHAR* ConfigSection = TEXT("AssetVerifier");
	const TCHAR* StaticMeshPrefixKey = TEXT("StaticMeshPrefix");

	inline void GetString(const FString& Key, FString& Value)
	{
		GConfig->GetString(
			ConfigSection,
			*Key,
			Value,
			GEditorPerProjectIni
		);
	}

	inline void SetString(const FString& Key, const FString& Value) const
	{
		GConfig->SetString(
			ConfigSection,
			*Key,
			*Value,
			GEditorPerProjectIni
		);
	}
};

