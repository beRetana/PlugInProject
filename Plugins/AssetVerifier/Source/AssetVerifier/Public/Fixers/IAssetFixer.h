#pragma once

struct FAssetValidationData;

class IAssetFixer
{
public:
	virtual ~IAssetFixer() = default;
	virtual void Fix(FAssetValidationData& Asset) = 0;
	virtual FName GetFixerName() const = 0;

private:
	IAssetFixer() = default;
};