// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetVerifier.h"

#include "Validators/AssetNamingValidator.h"

#include "Fixers/AssetNamingFixer.h"

#include "Reporting/AssetReportGenerator.h"

#include "UI/AssetVerifierSettingsWindow.h"
#include "UI/ValidationResultWindow.h"
#include "UI/IssuesDisplayView.h"

#include "Utils/VerifierUtils.h"

#include "AssetScopeBuilder.h"
#include "AssetVerifierCommands.h"
#include "Misc/MessageDialog.h"

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
	FixerManager = MakeShareable(new FFixerManager);
	VerifierSettings = MakeShareable(new FAssetVerifierSettings);

	VerifierSettings->OnSettingsChanged.AddRaw(this, &FAssetVerifier::ApplySettings);
	ValidatorManager->RegisterValidator<FAssetNamingValidator>(NamingValidatorName, NamingFixerName);
	FixerManager->RegisterFixer<FAssetNamingFixer>(NamingFixerName);
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
		FExecuteAction::CreateLambda([this]() {RunValidator(NamingValidatorName); })
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
	if (ValidationResultsWindow.IsValid())
	{
		ValidationResultsWindow->BringToFront(true);
		return;
	}

	double StartTime = FPlatformTime::Seconds();
	CurrentReport.Reset();
	FAssetScopeBuilder::BuildScopeAll(CurrentReport.Assets);
	ValidatorManager->ExecuteValidator(ValidatorName, CurrentReport.Assets, CurrentReport);
	FAssetReportGenerator::GenerateReport(CurrentReport);
	ShowReportWindow(CurrentReport, FPlatformTime::Seconds() - StartTime);
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
		UE_LOG(LogTemp, Warning, TEXT("The window already exists"));
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

	SettingsWindowUI->SetOnWindowClosed(FOnWindowClosed::CreateLambda([this](const TSharedRef<SWindow>&) 
		{
			SettingsWindowUI.Reset();
		}));
	
	FSlateApplication::Get().AddWindow(SettingsWindowUI.ToSharedRef());
}

void FAssetVerifier::ShowReportWindow(const VD::FAssetValidationReport& Report, double TimeElapsed)
{ 
	auto SaveToCSV = FSimpleDelegate::CreateLambda([Report]()
		{
			FAssetReportGenerator::SaveSmallReportToCSVFile(Report);
		});

	auto SaveToJSON = FSimpleDelegate::CreateLambda([Report]()
		{
			FAssetReportGenerator::SaveSmallReportToJSONFile(Report);
		});

	auto SaveToLog = FSimpleDelegate::CreateLambda([Report]()
		{
			FAssetReportGenerator::StreamSmallReportToLog(Report);
		});

	auto OpenIssuesWindow = FSimpleDelegate::CreateLambda([Report, this]() 
		{
			CreateIssuesWindow(Report);
		});

	ValidationResultsWindow = SNew(SWindow)
		.Title(LOCTEXT("AssetValidationReport", "Asset Validation Report"))
		.SizingRule(ESizingRule::Autosized)
		[
			SNew(SValidationResultWindow)
				.TimeStamp(TimeElapsed)
				.ErrorCountNum(Report.Summary.Errors)
				.OnSaveToCSV(SaveToCSV)
				.OnSaveToJSON(SaveToJSON)
				.OnStreamToLog(SaveToLog)
				.OnFixIssues(OpenIssuesWindow)
		]
		.SupportsMaximize(false)
		.SupportsMinimize(true);

	ValidationResultsWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda([this](const TSharedRef<SWindow>&) 
		{
			ValidationResultsWindow.Reset();
		}));

	FSlateApplication::Get().AddWindow(ValidationResultsWindow.ToSharedRef());
}

void FAssetVerifier::CreateIssuesWindow(const VD::FAssetValidationReport& Report)
{
	if (IssuesViewWindow.IsValid())
	{
		IssuesViewWindow->BringToFront(true);
		return;
	}

	TArray<TSharedPtr<VD::FAssetValidationData>> DataList;

	for (const auto& FixerData : Report.ValidatorToFixerData)
	{
		for (const auto& Issue : FixerData.Value.AllValidationData)
		{
			DataList.Add(MakeShared<VD::FAssetValidationData>(Issue));
		}
	}

	IssuesViewWindow = SNew(SWindow)
		.Title(FText::FromString("Issues View Table"))
		.ClientSize(FVector2d(1000, 500))
		.MinHeight(300.f)
		.MinWidth(600.f)
		.SizingRule(ESizingRule::UserSized)
		[
			SNew(SBox)
				[
					SNew(SIssueDisplayView)
						.DataList(DataList)
						.OnFixSelected(FSimpleDelegate::CreateLambda([this]() { RunFixer(); }))
				]
		]
		.SupportsMaximize(true)
		.SupportsMinimize(true);

	IssuesViewWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda([this](const TSharedRef<SWindow>&)
		{
			IssuesViewWindow.Reset();
		}));

	FSlateApplication::Get().AddWindow(IssuesViewWindow.ToSharedRef());
}

void FAssetVerifier::RunFixer()
{
	const auto UserAnswer = FMessageDialog::Open(
			EAppMsgType::OkCancel, 
			LOCTEXT("ConfirmFixer", "Running Fixers might change assets irreversibly.\nDo you still want to proceed?"),
			LOCTEXT("TitleConfirmFixer","Confirmation Needed!"));

	if (UserAnswer == EAppReturnType::Cancel) return;

	if (!FixerManager.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Missing pointer, the fixer manager was not set up properly"));
		return;
	}
	
	ValidationResultsWindow->RequestDestroyWindow();
	IssuesViewWindow->RequestDestroyWindow();
	FixerManager->ExecuteAllFixers(CurrentReport);
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("FixerResult", "Process has been completed successfully!"));
	FVerifierUtils::SaveDirtyAssets(CurrentReport.Assets);
	CurrentReport.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetVerifier, AssetVerifier)