#include "UI/IssuesDisplayView.h"
#include "Widgets/Input/SSearchBox.h"

void SIssueDisplayView::Construct(const FArguments& InArgs)
{
	AllDataList = InArgs._DataList;

	ChildSlot
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Left).Padding(10.0f)
				[
					SNew(STextBlock).Text(FText::FromString(PannelDescription))
				]
				+ SVerticalBox::Slot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Left).Padding(10.0f)
				[
					SNew(SSearchBox).OnTextChanged(this, &SIssueDisplayView::OnSearchKeyChanged)
				]
				+ SVerticalBox::Slot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Left).Padding(10.0f)
				[
					SAssignNew(ListViewPtr, SListView<DataPtr>)
						.ListItemsSource(&FilteredDataList)
						.OnGenerateRow(this, &SIssueDisplayView::GenerateRow)
						.SelectionMode(ESelectionMode::Multi)
						.HeaderRow
						(
							SNew(SHeaderRow)
							+ SHeaderRow::Column("Asset Name")
							+ SHeaderRow::Column("Result")
							+ SHeaderRow::Column("Validator")
							+ SHeaderRow::Column("Fixer")
							+ SHeaderRow::Column("Auto-Fixable")
							+ SHeaderRow::Column("Fix")
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