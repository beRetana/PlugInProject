#include "Fixers/FixerManager.h"
#include "Fixers/IAssetFixer.h"
#include "AssetValidationData.h"

void FFixerManager::ExecuteFixer(const FName& FixerName, TArray<TArray<FAssetValidationData>>& ValidationData)
{
	auto& Issues = ValidationData[static_cast<int32>(EValidationResult::Error_3)];
	
	if (auto* Fixer = FixersMap.Find(FixerName))
	{
		for (auto& Issue : Issues)
		{
			if (Issue.FixerName != FixerName) continue;

			Fixer->Fix(Issue);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fixer %s not found."), *FixerName.ToString());
	}
}

void FFixerManager::ExecuteFixers(const TArray<FName>& FixerNames, TArray<TArray<FAssetValidationData>>& ValidationData)
{
	for (const FName& FixerName : FixerNames)
	{
		ExecuteFixer(FixerName, ValidationData);
	}
}