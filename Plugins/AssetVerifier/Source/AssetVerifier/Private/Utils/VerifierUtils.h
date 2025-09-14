#pragma once

#include "AssetValidationData.h"

class FVerifierUtils
{
public:
	static void CleanupRedirector(const TArray<VD::DataPtr>& ValidationData);

	static void SaveDirtyAssets(const TArray<FAssetData>& ValidationData);

	static bool CheckoutInSourceControl(const TArray<UPackage*>& Packages);
};