#pragma once

struct FAssetData;
struct FAssetValidationData;

class FVerifierUtils
{
public:
	static void CleanupRedirector(const TArray<FAssetValidationData>& ValidationData);

	static void SaveDirtyAssets(const TArray<FAssetData>& ValidationData);

	static bool CheckoutInSourceControl(const TArray<UPackage*>& Packages);
};