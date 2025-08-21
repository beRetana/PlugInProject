// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

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
	void OpenSettingsWindow();
	void RunValidator(const FName& ValidatorName);
	void PopulateCommands(UToolMenu* InMenu);

	TSharedPtr<FUICommandList> Commands;
	TSharedPtr<class FValidatorManager> ValidatorManager;
	TSharedPtr<class FAssetVerifierSettings> VerifierSettings;
	TSharedPtr<class SWindow> SettingsWindowUI;

	FName StaticMeshNaming = TEXT("StaticMeshNamingValidator");
};
