#include "Fixers\AssetNamingFixer.h"
#include "AssetValidationData.h"
#include "AssetToolsModule.h"

void FAssetNamingFixer::Fix(FFixerData& FixerData)
{
	for (const auto& ValidationData : FixerData[EValidationResult::Error_3])
	{
		ChangeName(ValidationData);
	}
}

void FAssetNamingFixer::ChangeName(const FAssetValidationData& ValidationData)
{

}

FName FAssetNamingFixer::GetFixerName() const
{
	return FName(FIXER_NAME);
}