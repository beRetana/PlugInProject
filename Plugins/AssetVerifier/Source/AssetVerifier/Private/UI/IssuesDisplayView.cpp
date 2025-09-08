#include "UI/IssuesDisplayView.h"
#include "UI/IssueRowWidget.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "IssuesDisplayViewUI"

void SIssueDisplayView::Construct(const FArguments& InArgs)
{
	AllDataList = InArgs._DataList;
	OnFixSelectedAction = InArgs._OnFixSelected;

	ChildSlot
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill).Padding(10.0f)
				[
					SNew(STextBlock)
						.Text(FText::FromString(PannelDescription))
						.AutoWrapText(true)
				] 
				+ SVerticalBox::Slot().Padding(10).AutoHeight().HAlign(HAlign_Left)
				[
					SNew(SButton)
						.OnClicked(this, &SIssueDisplayView::OnFixSelectedIssues)
						.Text(LOCTEXT("FixBtn", "Fix Selected Assets"))
				]
				+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill).Padding(10.0f)
				[
					SNew(SSearchBox)
						.OnTextChanged_Raw(this, &SIssueDisplayView::OnSearchKeyChanged)
				]
				+ SVerticalBox::Slot()
					.HAlign(EHorizontalAlignment::HAlign_Fill)
					.Padding(10.0f)
				[
					SAssignNew(ListViewPtr, SListView<DataPtr>)
						.ListItemsSource(&FilteredDataList)
						.OnGenerateRow(this, &SIssueDisplayView::GenerateRow)
						.SelectionMode(ESelectionMode::Multi)
						.HeaderRow
						(
							SNew(SHeaderRow)
							+ SHeaderRow::Column(SIssueRowWidget::ASSET)
								.DefaultLabel(LOCTEXT("Asset", "Asset Name"))
								.FillWidth(.4)
							+ SHeaderRow::Column(SIssueRowWidget::RESULT)
								.DefaultLabel(LOCTEXT("Result", "Result"))
								.FillWidth(.1)
							+ SHeaderRow::Column(SIssueRowWidget::VALIDATOR)
								.DefaultLabel(LOCTEXT("ValidatorName", "Validator"))
								.FillWidth(.2)
							+ SHeaderRow::Column(SIssueRowWidget::FIXER)
								.DefaultLabel(LOCTEXT("FixerName", "Fixer"))
								.FillWidth(.2)
							+ SHeaderRow::Column(SIssueRowWidget::AUTO_FIX)
								.DefaultLabel(LOCTEXT("CanFix", "Auto Fix-able"))
								.FixedWidth(100.f)
							+ SHeaderRow::Column(SIssueRowWidget::FIX)
								.DefaultLabel(LOCTEXT("SelectFix", "Select Fix"))
								.FixedWidth(80.f)
						)
				]
		];

	ApplyFilter(TEXT(""));
}

TSharedRef<ITableRow> SIssueDisplayView::GenerateRow(DataPtr DataPtr, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SIssueRowWidget, Owner).ValidationData(DataPtr);
}

void SIssueDisplayView::SetDataList(const TArray<FAssetValidationData>& NewDataList)
{
	AllDataList.Reset();
	AllDataList.Reserve(NewDataList.Num());

	for (const auto& DataItem : NewDataList)
	{
		AllDataList.Add(MakeShared<FAssetValidationData>(DataItem));
	}

	ApplyFilter(CurrentFilterKey);
}

void SIssueDisplayView::ApplyFilter(const FString& FilterKey)
{
	if (FilterKey == TEXT(""))
	{
		FilteredDataList = AllDataList;
	}

	FilteredDataList.Reset();
	CurrentFilterKey = FilterKey;

	for (const auto& Data : AllDataList)
	{
		if (!Data.IsValid()) continue;
		if (!ContainsFilterKey(Data)) continue;

		FilteredDataList.Add(Data);
	}

	if (!ListViewPtr.IsValid()) return;

	ListViewPtr->RequestListRefresh();
}

bool SIssueDisplayView::ContainsFilterKey(const DataPtr& Data)
{
	return Data->Asset->AssetName.ToString().Contains(CurrentFilterKey) ||
		Data->ResultString().Contains(CurrentFilterKey) ||
		Data->ValidatorName.ToString().Contains(CurrentFilterKey) ||
		Data->FixerName.ToString().Contains(CurrentFilterKey) ||
		FString((Data->bCanAutoFix) ? TEXT("true") : TEXT("false")).Contains(CurrentFilterKey);
}

void SIssueDisplayView::OnSearchKeyChanged(const FText& NewSearchKey)
{
	ApplyFilter(NewSearchKey.ToString());
}

FReply SIssueDisplayView::OnFixSelectedIssues()
{
	if (OnFixSelectedAction.IsBound())
	{
		OnFixSelectedAction.Execute();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Action Delegate NOT bound"));
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE