#pragma once 
#include "CoreMinimal.h"
#include "Fixers/IAssetFixer.h"

class FAssetVerifierSettings;
struct FAssetValidationReport;

class FFixerManager
{
public:

	void ExecuteFixer(const FName& FixerName, FAssetValidationReport& Report);
	void ExecuteFixers(const TArray<FName>& FixerNames, FAssetValidationReport& Report);
	void ApplySettings(const FAssetVerifierSettings& Settings);

	template<typename TFixer, typename... TArgs>
	void RegisterFixer(const FName& FixerName, TArgs&&... Arguments)
	{
		static_assert(TIsDerivedFrom<TFixer, IAssetFixer>::Value, "Class must inherit from IAssetFixer");

		if (FixersMap.Contains(FixerName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Fixer %s is already registered."), *FixerName.ToString());
			return;
		}

		FixersMap.Add(FixerName, MakeUnique<TFixer>(Forward<TArgs>(Arguments)...));
	}

private:
	
	TMap<FName, TUniquePtr<IAssetFixer>> FixersMap;
};