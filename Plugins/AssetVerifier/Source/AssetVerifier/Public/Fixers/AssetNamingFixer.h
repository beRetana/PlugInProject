#pragma once

#include "Fixers/IAssetFixer.h"

class FAssetNamingFixer : public IAssetFixer
{
public:
	void Fix(FFixerData& FixerData) override;
	void ChangeName(const FAssetValidationData& ValidationData);
	FName GetFixerName() const override;

private:
	const TCHAR* FIXER_NAME = TEXT("AssetNameFixer");
};