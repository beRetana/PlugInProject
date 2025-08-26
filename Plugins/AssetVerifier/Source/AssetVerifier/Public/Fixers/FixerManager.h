#pragma once 

class FAssetVerifierSettings;

class FFixerManager
{
public:

	void ExecuteFixer(const FName& FixerName, TArray<TArray<struct FAssetValidationData>>& ValidationData);
	void ExecuteFixers(const TArray<FName>& FixerNames, TArray<TArray<struct FAssetValidationData>>& ValidationData);
	void ApplySettings(const FAssetVerifierSettings& Settings);

	template<typename TFixer, typename... TArgs>
	void RegisterFixer(const FName& FixerName, TArgs&&... Arguments)
	{
		static_assert(TIsDerivedFrom < TFixer, class IAssetFixer>::IsDerived, "Class must inherit from IAssetFixer");

		if (FixersMap.Contains(FixerName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Fixer %s is already registered."), *FixerName.ToString());
			return;
		}

		FixersMap.Add(FixerName, MakeUnique<TFixer>(Forward<TArgs>()...));
	}

private:
	
	TSortedMap<FName, class IAssetFixer> FixersMap;
};