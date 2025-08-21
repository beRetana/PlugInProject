
#include "AssetVerifierSettings.h"

void FAssetVerifierSettings::LoadSettings()
{
	GetString(StaticMeshPrefixKey, StaticMeshPrefixValue);

	// Other Settings can be loaded here
}

void FAssetVerifierSettings::SaveSettings() const
{
	SetString(StaticMeshPrefixKey, StaticMeshPrefixValue);
	GConfig->Flush(true, GEditorIni);
	OnSettingsChanged.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Saved StaticMeshPrefix: %s"), *StaticMeshPrefixValue);
}