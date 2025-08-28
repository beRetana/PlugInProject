#pragma once 

class FAssetVerifierSettings;

class FFixerManager
{
public:

	void ExecuteFixer(const FName& FixerName, FAssetValidationReport& Report);
	void ExecuteFixers(const TArray<FName>& FixerNames, FAssetValidationReport& Report);
	void ApplySettings(const FAssetVerifierSettings& Settings);

	template<typename TFixer, typename... TArgs>
	void RegisterFixer(const FName& FixerName, TArgs&&... Arguments)
	{
		static_assert(TIsDerivedFrom<TFixer, class IAssetFixer>::IsDerived, "Class must inherit from IAssetFixer");

		if (FixersMap.Contains(FixerName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Fixer %s is already registered."), *FixerName.ToString());
			return;
		}

		FixersMap.Add(FixerName, MakeUnique<TFixer>(Forward<TArgs>()...));
	}

private:
	
	TMap<FName, class IAssetFixer> FixersMap;
};