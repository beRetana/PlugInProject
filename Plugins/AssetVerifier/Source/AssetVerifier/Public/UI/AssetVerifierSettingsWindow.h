#pragma once

#include "Widgets/SCompoundWidget.h"

class FAssetVerifierSettings;
class FAssetVerfier;

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