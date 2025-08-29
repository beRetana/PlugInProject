// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetValidationData.h"

class FAssetVerifier : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void LoadSettings();
	void ApplySettings();

private:

	void SetUpDependencies();
	void MapCommands();
	void SetUpUI();
	void SetUpValidationData(TArray<TArray<FAssetValidationData>>& OutData);
	void ShowReportWindow(const FAssetValidationReport& Report, double TimeElapsed);
	void OpenSettingsWindow();
	void RunValidator(const FName& ValidatorName);
	void PopulateCommands(UToolMenu* InMenu);

	TSharedPtr<FUICommandList> Commands;
	TSharedPtr<class FValidatorManager> ValidatorManager;
	TSharedPtr<class FAssetVerifierSettings> VerifierSettings;
	TSharedPtr<class SWindow> SettingsWindowUI;
	TSharedPtr<class SWindow> ValidationResultsWindow;
	// pointer to issues display window
	
	FAssetValidationReport CurrentReport;
	TArray<FAssetData> CurrentAssetBatch;

	const FName NamingValidatorName = TEXT("NamingValidator");
	const FName NamingFixerName = TEXT("NamingFixer");
};
