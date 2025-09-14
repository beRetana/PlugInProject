#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "AssetVerifierSettings.h"

class SAssetVerifierSettingsWindow : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SAssetVerifierSettingsWindow) {}
		SLATE_ARGUMENT(TSharedPtr<FAssetVerifierSettings>, VerifierSettings);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	TSharedPtr<FAssetVerifierSettings> VerifierSettings;
	TSharedPtr<class SEditableTextBox> StaticMeshPrefixTextBox;

	FReply OnSavedClicked();
};