#pragma once

struct FFixerData;

class IAssetFixer
{
public:
	virtual ~IAssetFixer() = default;
	virtual void Fix(FFixerData& Asset) = 0;
	virtual FName GetFixerName() const = 0;

private:
	IAssetFixer() = default;
};