
#include "AssetVerifierSettingsWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "AssetVerifierSettings.h"

void SAssetVerifierSettingsWindow::Construct(const FArguments& InArgs)
{
	VerifierSettings = InArgs._VerifierSettings;

	ChildSlot
	[
		SNew(SVerticalBox) 
		+ SVerticalBox::Slot().AutoHeight().Padding(5.0f)
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(5.0f).VAlign(VAlign_Center)
			[
				SNew(STextBlock)
					.Text(FText::FromString("Static Meshes Prefix:"))
			]
			+ SHorizontalBox::Slot().AutoWidth().Padding(5.0f)
			[
				SAssignNew(StaticMeshPrefixTextBox, SEditableTextBox)
					.Text(FText::FromString(VerifierSettings.IsValid() ? VerifierSettings->StaticMeshPrefixValue : ""))
			]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(5.0f).HAlign(HAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().Padding(5.0f).HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SButton)
					.Text(FText::FromString("Save"))
					.OnClicked(this, &SAssetVerifierSettingsWindow::OnSavedClicked)
			]
		]
	];
}

FReply SAssetVerifierSettingsWindow::OnSavedClicked()
{
	if (VerifierSettings.IsValid() && StaticMeshPrefixTextBox.IsValid())
	{
		VerifierSettings->StaticMeshPrefixValue = StaticMeshPrefixTextBox->GetText().ToString();
		VerifierSettings->SaveSettings();
	}

	return FReply::Handled();
}