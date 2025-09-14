// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetValidationData.h"
#include "Validators/ValidatorManager.h"
#include "Fixers/FixerManager.h"
#include "AssetVerifierSettings.h"

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
	void ShowReportWindow(const VD::FAssetValidationReport& Report, double TimeElapsed);
	void OpenSettingsWindow();
	void CreateIssuesWindow(const VD::FAssetValidationReport& Report);
	void RunValidator(const FName& ValidatorName);
	void RunFixer();
	void PopulateCommands(UToolMenu* InMenu);

private:
	VD::FAssetValidationReport CurrentReport;

	TSharedPtr<FUICommandList> Commands;
	TSharedPtr<FValidatorManager> ValidatorManager;
	TSharedPtr<FFixerManager> FixerManager;
	TSharedPtr<FAssetVerifierSettings> VerifierSettings;
	TSharedPtr<SWindow> SettingsWindowUI;
	TSharedPtr<SWindow> ValidationResultsWindow;
	TSharedPtr<SWindow> IssuesViewWindow;

	TArray<FAssetData> CurrentAssetBatch;

	const FName NamingValidatorName = TEXT("Naming Validator");
	const FName NamingFixerName = TEXT("Naming Fixer");
};
