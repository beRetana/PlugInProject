#include "UI/IssueRowWidget.h"

void SIssueRowWidget::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
{
	ValidationData = InArgs._ValidationData;

	SMultiColumnTableRow<VD::DataPtr>::Construct(
		SMultiColumnTableRow<VD::DataPtr>::FArguments().Padding(FMargin(1.0f, 1.0f)), Owner);
}

TSharedRef<SWidget> SIssueRowWidget::GenerateWidgetForColumn(const FName& ColumnName)
{
	if (ColumnName == ASSET)
	{
		return SNew(SBox).Padding(5).VAlign(VAlign_Center).HAlign(HAlign_Left)
			[
				SNew(STextBlock).
					Text(FText::FromName(ValidationData->Asset->AssetName))
			];
	}

	if (ColumnName == RESULT)
	{
		return SNew(SBox).Padding(5).VAlign(VAlign_Center).HAlign(HAlign_Left)
			[
				SNew(STextBlock).Text(FText::FromString(ValidationData->ResultString()))
					.ColorAndOpacity(GetResultColor(ValidationData->Result))
			];
	}

	if (ColumnName == VALIDATOR)
	{
		return SNew(SBox).Padding(5).VAlign(VAlign_Center).HAlign(HAlign_Left)
			[
				SNew(STextBlock).Text(FText::FromName(ValidationData->ValidatorName))
			];
	}

	if (ColumnName == FIXER)
	{
		return SNew(SBox).Padding(5).VAlign(VAlign_Center).HAlign(HAlign_Left)
			[
				SNew(STextBlock).Text(FText::FromName(ValidationData->FixerName))
			];
	}

	if (ColumnName == AUTO_FIX)
	{
		return SNew(SBox).Padding(5).VAlign(VAlign_Center).HAlign(HAlign_Left)
			[
				SNew(STextBlock).Text(FText::FromString(ValidationData->bCanAutoFix ? TEXT("Yes") : TEXT("No")))
			];
	}

	if (ColumnName == FIX)
	{
		if (ValidationData->bCanAutoFix) ValidationData->bSelectedFix = true;

		return SNew(SBox)
			.Padding(5)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
					.HAlign(HAlign_Center)
					.IsEnabled_Lambda([this]()
						{
							return ValidationData->bCanAutoFix;
						})
					.IsChecked_Lambda([this]()
						{
							return ValidationData->bSelectedFix ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; 
						})
					.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
						{ 
							ValidationData->bSelectedFix = NewState == ECheckBoxState::Checked; 
						})
			];
	}

	return SNullWidget::NullWidget;
}

FSlateColor SIssueRowWidget::GetResultColor(const VD::EValidationResult& Result)
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