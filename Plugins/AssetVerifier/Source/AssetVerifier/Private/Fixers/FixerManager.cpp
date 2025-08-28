#include "Fixers/FixerManager.h"
#include "Fixers/IAssetFixer.h"
#include "AssetValidationData.h"

void FFixerManager::ExecuteFixer(const FName& FixerName, FAssetValidationReport& Report)
{
	if (auto* Fixer = FixersMap.Find(FixerName))
	{
		if (auto* FixerData = Report.ValidatorToFixerData.Find(FixerName))
		{
			Fixer->Fix(*FixerData); 
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("No validation data found for fixer %s."), *FixerName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fixer %s not found."), *FixerName.ToString());
	}
}

void FFixerManager::ExecuteFixers(const TArray<FName>& FixerNames, FAssetValidationReport& Report)
{
	for (const FName& FixerName : FixerNames)
	{
		ExecuteFixer(FixerName, Report);
	}
}