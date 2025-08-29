#pragma once

#include "Fixers/IAssetFixer.h"

class FAssetNamingFixer : public IAssetFixer
{
public:
	void Fix(FFixerData& FixerData) override;
	FName GetFixerName() const override;

private:
	const TCHAR* FIXER_NAME = TEXT("AssetNameFixer");
};