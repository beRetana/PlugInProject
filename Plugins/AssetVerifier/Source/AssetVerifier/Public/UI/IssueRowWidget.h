#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"

typedef TSharedRef<FAssetValidationData> ValidationDataRef;

class SIssueRowWidget : public SMultiColumnTableRow<ValidationDataRef>
{
public:
	SLATE_BEGIN_ARGS(SIssueRowWidget) {}
		SLATE_ARGUMENT(ValidationDataRef, ValidationData)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;

private:
	ValidationDataRef ValidationData;

	FSlateColor RedFontColor{ FLinearColor(0.9f, 0.15f, 0.15f, 1.f) };
};