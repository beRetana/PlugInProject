#pragma once

#include "Framework/Commands/Commands.h"
#include "Styling/AppStyle.h"

class FAssetVerifierCommands : public TCommands<FAssetVerifierCommands>
{
public:
	FAssetVerifierCommands() : TCommands<FAssetVerifierCommands>(
		TEXT("AssetVerification"),
		NSLOCTEXT("Contexts", "AssetVerification", "Asset Verification Plug-in"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> OpenSettingsWindow;
	TSharedPtr<FUICommandInfo> OpenValidatorsSection;
	TSharedPtr<FUICommandInfo> OpenFixersSection;

	TSharedPtr<FUICommandInfo> RunAllValidators;
	TSharedPtr<FUICommandInfo> RunSelectedValidator;

	TSharedPtr<FUICommandInfo> RunAllFixers;
	TSharedPtr<FUICommandInfo> RunSelectedFixer;

	TSharedPtr<FUICommandInfo> CheckStaticMeshNames;

private:

	// Short-Cuts for Commands 

	inline FInputChord KeyPlusShift(FKey Key) { return FInputChord(Key, true, false, false, false); }
	inline FInputChord KeyPlusCtrl(FKey Key) { return FInputChord(Key, false, true, false, false); }
	inline FInputChord KeyPlusAlt(FKey Key) { return FInputChord(Key, false, false, true, false); }
	inline FInputChord KeyPlusCmd(FKey Key) { return FInputChord(Key, false, false, false, true); }
};


