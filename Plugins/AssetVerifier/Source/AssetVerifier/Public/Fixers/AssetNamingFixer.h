#pragma once

#include "Fixers/IAssetFixer.h"

class FAssetNamingFixer : public IAssetFixer
{
public:
	FAssetNamingFixer(FName FixerName = TEXT("Naming Fixer")): FixerName(FixerName){}

	void Fix(FFixerData& FixerData) override;
	FName GetFixerName() const override;

private:
	FName FixerName;
};