#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"

class SIssueRowWidget : public SMultiColumnTableRow<VD::DataPtr>
{
public:
	SLATE_BEGIN_ARGS(SIssueRowWidget) {}
		SLATE_ARGUMENT(VD::DataPtr, ValidationData)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;

	static FSlateColor GetResultColor(const VD::EValidationResult& Result);

public:

	static inline FName ASSET = "Asset Name";
	static inline FName RESULT = "Result";
	static inline FName VALIDATOR = "Validator";
	static inline FName FIXER = "Fixer";
	static inline FName AUTO_FIX = "Auto Fix-able";
	static inline FName FIX = "Select Fix";

private:
	VD::DataPtr ValidationData;

	static inline FSlateColor RedFontColor{ FLinearColor::FromSRGBColor(FColor(230,38,38,255)) };
	static inline FSlateColor GreenFontColor{ FLinearColor::FromSRGBColor(FColor(19, 176, 14, 255)) };
	static inline FSlateColor YellowFontColor{ FLinearColor::FromSRGBColor(FColor(255.f, 209.f, 35.f, 255)) };
	static inline FSlateColor BlueFontColor{ FLinearColor::FromSRGBColor(FColor(10.f, 112.f, 255.f, 255)) };
};