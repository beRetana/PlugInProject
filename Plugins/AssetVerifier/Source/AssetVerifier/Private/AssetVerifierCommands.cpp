
#include "AssetVerifierCommands.h"
#include "InputCoreTypes.h"

#define LOCTEXT_NAMESPACE "AssetVerifierCommands"

void FAssetVerifierCommands::RegisterCommands()
{
	UI_COMMAND
	(
		CheckStaticMeshNames,
		"Validate Static Mesh Naming",
		"Checks if Static Meshes follow naming convention",
		EUserInterfaceActionType::Button,
		KeyPlusCtrl(EKeys::M)
	);

	UI_COMMAND
	(
		OpenSettingsWindow,
		"Verifier Settings",
		"Opens a Window to customize settings",
		EUserInterfaceActionType::Button,
		KeyPlusShift(EKeys::P)
	);
}

#undef LOCTEXT_NAMESPACE