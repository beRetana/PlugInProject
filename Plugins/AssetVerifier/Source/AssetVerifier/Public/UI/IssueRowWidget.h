#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"

typedef TSharedPtr<FAssetValidationData> DataPtr;

class SIssueRowWidget : public SMultiColumnTableRow<DataPtr>
{
public:
	SLATE_BEGIN_ARGS(SIssueRowWidget) {}
		SLATE_ARGUMENT(DataPtr, ValidationData)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;

	static inline FName ASSET = "Asset Name";
	static inline FName RESULT = "Result";
	static inline FName VALIDATOR = "Validator";
	static inline FName FIXER = "Fixer";
	static inline FName AUTO_FIX = "Auto Fix-able";
	static inline FName FIX = "Select Fix";

private:
	DataPtr ValidationData;

	FSlateColor RedFontColor{ FLinearColor(0.9f, 0.15f, 0.15f, 1.f) };
};