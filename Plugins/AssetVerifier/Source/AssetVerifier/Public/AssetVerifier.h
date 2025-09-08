// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetValidationData.h"

class SWindow;

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
	void CreateIssuesWindow(const FAssetValidationReport& Report);
	void RunValidator(const FName& ValidatorName);
	void RunFixer();
	void PopulateCommands(UToolMenu* InMenu);

private:
	FAssetValidationReport CurrentReport;

	TSharedPtr<FUICommandList> Commands;
	TSharedPtr<class FValidatorManager> ValidatorManager;
	TSharedPtr<class FFixerManager> FixerManager;
	TSharedPtr<class FAssetVerifierSettings> VerifierSettings;
	TSharedPtr<SWindow> SettingsWindowUI;
	TSharedPtr<SWindow> ValidationResultsWindow;
	TSharedPtr<SWindow> IssuesViewWindow;

	TArray<FAssetData> CurrentAssetBatch;

	const FName NamingValidatorName = TEXT("Naming Validator");
	const FName NamingFixerName = TEXT("Naming Fixer");
};
