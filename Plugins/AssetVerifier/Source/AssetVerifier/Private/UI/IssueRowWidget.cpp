#include "UI/IssueRowWidget.h"

void SIssueRowWidget::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
{
	ValidationData = InArgs._ValidationData;

	SMultiColumnTableRow<DataPtr>::Construct(
		SMultiColumnTableRow<DataPtr>::FArguments(), Owner);
}

TSharedRef<SWidget> SIssueRowWidget::GenerateWidgetForColumn(const FName& ColumnName)
{
	if (ColumnName == "Asset Name")
	{
		return SNew(STextBlock).Text(FText::FromName(ValidationData->Asset->AssetName));
	}

	if (ColumnName == "Result")
	{
		return SNew(STextBlock).Text(FText::FromString(ValidationData->ResultString()))
			.ColorAndOpacity(RedFontColor);
	}

	if (ColumnName == "Validator")
	{
		return SNew(STextBlock).Text(FText::FromName(ValidationData->ValidatorName));
	}

	if (ColumnName == "Fixer")
	{
		return SNew(STextBlock).Text(FText::FromName(ValidationData->FixerName));
	}

	if (ColumnName == "Auto-Fixable")
	{
		return SNew(STextBlock).Text(FText::FromString(ValidationData->bCanAutoFix ? TEXT("Yes") : TEXT("No")));
	}

	if (ColumnName == "Fix")
	{
		return SNew(SCheckBox).IsChecked_Lambda([this]() 
			{return ValidationData->bSelectedFix ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
			.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
				{ ValidationData->bSelectedFix = NewState == ECheckBoxState::Checked; });
	}

	return SNullWidget::NullWidget;
}