#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"

typedef TSharedPtr<VD::FAssetValidationData> DataPtr;

class SIssueRowWidget : public SMultiColumnTableRow<DataPtr>
{
public:
	SLATE_BEGIN_ARGS(SIssueRowWidget) {}
		SLATE_ARGUMENT(DataPtr, ValidationData)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;

private:

	inline static FSlateColor GetResultColor(const VD::EValidationResult& Result)
	{
		switch (Result)
		{
			case VD::EValidationResult::Passed_0:
				return GreenFontColor;
			case VD::EValidationResult::Information_1:
				return BlueFontColor;
			case VD::EValidationResult::Warning_2:
				return YellowFontColor;
			default:
				return RedFontColor;
		}
	}

public:

	static inline FName ASSET = "Asset Name";
	static inline FName RESULT = "Result";
	static inline FName VALIDATOR = "Validator";
	static inline FName FIXER = "Fixer";
	static inline FName AUTO_FIX = "Auto Fix-able";
	static inline FName FIX = "Select Fix";

private:
	DataPtr ValidationData;

	static inline FSlateColor RedFontColor{ FLinearColor(0.9f, 0.15f, 0.15f, 1.f) };
	static inline FSlateColor GreenFontColor{ FLinearColor(19.f, 176.f, 14.f, 0.8f) };
	static inline FSlateColor YellowFontColor{ FLinearColor(255.f, 209.f, 35.f, 0.8f) };
	static inline FSlateColor BlueFontColor{ FLinearColor(10.f, 112.f, 255.f, 0.8f) };
};