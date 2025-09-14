#pragma once

#include "CoreMinimal.h"
#include "AssetValidationData.h"

class IAssetFixer
{
public:

	virtual ~IAssetFixer() = default;
	virtual void Fix(VD::FFixerData& Asset) = 0;
	virtual FName GetFixerName() const = 0;

protected:
	IAssetFixer() = default;
};