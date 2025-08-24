#include "UI/ValidationResultWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void SValidationResultWindow::Construct(const FArguments& InArgs)
{
	TimeStampValue = InArgs._TimeStamp;
	OnSaveToCSV = InArgs._OnSaveToCSV;
	OnSaveToJSON = InArgs._OnSaveToJSON;
	OnStreamToLog = InArgs._OnStreamToLog;

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0,10.0f,0,0)
			[
				SNew(STextBlock)
					.Text(TimeStamp())
			]
				+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0,5.0f,0,0)
			[
				SNew(STextBlock)
					.Text(FText::FromString(TEXT("How would you like to save the results?")))
			]
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(5.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(5.0f)
				[
					SNew(SButton)
						.Text(FText::FromString(TEXT("Save to CSV")))
						.OnClicked(this, &SValidationResultWindow::HandleSaveToCSV)
				]
				+ SHorizontalBox::Slot().AutoWidth().Padding(5.0f)
				[
					SNew(SButton)
						.Text(FText::FromString(TEXT("Save to JSON")))
						.OnClicked(this, &SValidationResultWindow::HandleSaveToJSON)
				]
				+ SHorizontalBox::Slot().AutoWidth().Padding(5.0f)
				[
					SNew(SButton)
						.Text(FText::FromString(TEXT("Stream to Log")))
						.OnClicked(this, &SValidationResultWindow::HandleStreamToLog)
				]
			]
		];
}

FReply SValidationResultWindow::HandleSaveToCSV()
{
	if (OnSaveToCSV.IsBound())
	{
		OnSaveToCSV.Execute();
	}
	return FReply::Handled();
}

FReply SValidationResultWindow::HandleSaveToJSON()
{
	if (OnSaveToJSON.IsBound())
	{
		OnSaveToJSON.Execute();
	}
	return FReply::Handled();
}

FReply SValidationResultWindow::HandleStreamToLog()
{
	if (OnStreamToLog.IsBound())
	{
		OnStreamToLog.Execute();
	}
	return FReply::Handled();
}

const FText SValidationResultWindow::TimeStamp()
{
	return FText::FromString(FString::Printf(TEXT("Validation Report Completed in %0.2f secs"), TimeStampValue));
}