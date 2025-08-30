#include "UI/IssuesDisplayView.h"
#include "Widgets/Input/SSearchBox.h"

void SIssueDisplayView::Construct(const FArguments& InArgs)
{
	SetDataList(InArgs._DataList);

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
					SAssignNew(DataDisplayWidget, SListView<ValidationDataRef>)
						.
				]
		];
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

void SIssueDisplayView::ApplyFilter(const FText& FilterKey)
{

}

void SIssueDisplayView::OnSearchKeyChanged(const FText& NewSearchKey)
{
	ApplyFilter(NewSearchKey);
}