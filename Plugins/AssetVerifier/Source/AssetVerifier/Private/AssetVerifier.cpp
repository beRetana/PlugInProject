// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetVerifier.h"
#include "ValidatorManager.h"
#include "Reporting/AssetReportGenerator.h"
#include "AssetValidationData.h"
#include "AssetScopeBuilder.h"
#include "AssetVerifierCommands.h"
#include "AssetVerifierSettingsWindow.h"
#include "AssetVerifierSettings.h"
#include "Validators/AssetNamingValidator.h"

#define LOCTEXT_NAMESPACE "FAssetVerifierModule"

/// <summary>
/// Registers the module, sets up dependencies, loads settings, applies them,
/// </summary>
void FAssetVerifier::StartupModule()
{
	FAssetVerifierCommands::Register();

	SetUpDependencies();
	LoadSettings();
	ApplySettings();
	MapCommands();

	auto SetUpUI = FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetVerifier::SetUpUI);
	
	UToolMenus::RegisterStartupCallback(SetUpUI);
}

/// <summary>
/// Creates pointers for the commands, validators, and settings, and subscribes to
/// necessary callbacks/events.
/// </summary>
void FAssetVerifier::SetUpDependencies()
{
	Commands = MakeShareable(new FUICommandList);
	ValidatorManager = MakeShareable(new FValidatorManager);
	VerifierSettings = MakeShareable(new FAssetVerifierSettings);

	VerifierSettings->OnSettingsChanged.AddRaw(this, &FAssetVerifier::ApplySettings);
	ValidatorManager->RegisterValidator<FAssetNamingValidator>(StaticMeshNaming);
}

/// <summary>
/// Loads the settings into dependencies instances.
/// </summary>
void FAssetVerifier::LoadSettings()
{
	if (!VerifierSettings.IsValid())
	{
		VerifierSettings = MakeShareable(new FAssetVerifierSettings);
	}

	VerifierSettings->LoadSettings();
}

/// <summary>
/// Applies the settings to the AssetNamingValidator instance.
/// </summary>
void FAssetVerifier::ApplySettings()
{
	ValidatorManager->ApplySettings(*VerifierSettings);
}

/// <summary>
/// Maps the commands to their respective actions.
/// </summary>
void FAssetVerifier::MapCommands()
{
	Commands->MapAction(
		FAssetVerifierCommands::Get().CheckStaticMeshNames,
		FExecuteAction::CreateLambda([this]() {RunValidator(StaticMeshNaming); })
	);

	Commands->MapAction(
		FAssetVerifierCommands::Get().OpenSettingsWindow,
		FExecuteAction::CreateRaw(this, &FAssetVerifier::OpenSettingsWindow)
	);
}

/// <summary>
/// Create a section in the Level Editor main menu and create a submenu.
/// </summary>
void FAssetVerifier::SetUpUI()
{ 
	FToolMenuOwnerScoped OwnerScope("AssetVerification");
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");

	FToolMenuSection& PlugInMenuSection = ToolbarMenu->FindOrAddSection("Plug-In Section", LOCTEXT("UI_SECTION","Section Container"));

	auto PopulateCommands = FNewToolMenuDelegate::CreateRaw(this, &FAssetVerifier::PopulateCommands);
	
	PlugInMenuSection.AddEntry(FToolMenuEntry::InitSubMenu
	(
		"AssetVerifierTopMenu",
		LOCTEXT("UI_Section_Label", "Asset Verifier"),
		LOCTEXT("UI_Section_Tooltip", "Asset verification tools"),
		PopulateCommands,
		false, // Should Submenu show only once clicked?
		FSlateIcon()
	));
}

/// <summary>
/// Create a section for Actions in the submenu and add commands
/// </summary>
/// <param name="InMenu"></param>
void FAssetVerifier::PopulateCommands(UToolMenu* InMenu)
{
	FToolMenuSection& ActionSection = InMenu->AddSection("AssetVerifierActions", LOCTEXT("AssetVerifierActions", "Actions"));

	ActionSection.AddMenuEntryWithCommandList(
		FAssetVerifierCommands::Get().CheckStaticMeshNames,
		Commands
	);

	FToolMenuSection& SettingsSection = InMenu->AddSection("AssetVerifierSettings", LOCTEXT("AssetVerifierSettings", "Settings"));

	SettingsSection.AddMenuEntryWithCommandList(
		FAssetVerifierCommands::Get().OpenSettingsWindow,
		Commands
	);
}

/// <summary>
/// Unregisters the module, removes all callbacks, and unregisters the commands.
/// </summary>
void FAssetVerifier::ShutdownModule()
{
	VerifierSettings->OnSettingsChanged.RemoveAll(this);
	FAssetVerifierCommands::Unregister();
	UToolMenus::UnregisterOwner(this);
}

/// <summary>
/// Checks for naming conventions on Static Meshes.
/// </summary>
void FAssetVerifier::RunValidator(const FName& ValidatorName)
{
	TArray<FAssetValidationData> ValidationData;
	TArray<FAssetData> Assets = FAssetScopeBuilder::BuildScopeAll();
	ValidatorManager->ExecuteValidator(ValidatorName, Assets, ValidationData);
	FAssetValidationReport Report = FAssetReportGenerator::GenerateReport(ValidationData);
	bool bWasCSVSaved = FAssetReportGenerator::SaveSmallReportToCSVFile(Report);
	UE_LOG(LogTemp, Log, TEXT("Was the CSV Successfully Saved? %s"), bWasCSVSaved ? TEXT("true") : TEXT("false"));
}

/// <summary>
/// Creates a Slate window for the settings or brings the existing one to top.
/// </summary>
void FAssetVerifier::OpenSettingsWindow()
{
	if (!VerifierSettings.IsValid())
	{
		VerifierSettings = MakeShareable(new FAssetVerifierSettings);
		VerifierSettings->SaveSettings();
	}

	if (SettingsWindowUI.IsValid())
	{
		SettingsWindowUI->BringToFront(true);
		return;
	}

	SettingsWindowUI = SNew(SWindow)
		.Title(LOCTEXT("AssetVerifierSettings", "Asset Verifier Settings"))
		.SizingRule(ESizingRule::Autosized)
		[
			SNew(SAssetVerifierSettingsWindow).VerifierSettings(VerifierSettings)
		]
		.SupportsMaximize(true)
		.SupportsMinimize(true);
	
	FSlateApplication::Get().AddWindow(SettingsWindowUI.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetVerifier, AssetVerifier)