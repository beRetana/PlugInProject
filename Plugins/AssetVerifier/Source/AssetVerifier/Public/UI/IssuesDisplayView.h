#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"
#include "UI/IssueRowWidget.h"

DECLARE_DELEGATE(FOnFixSelected);

class SIssueDisplayView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SIssueDisplayView) {}
		SLATE_ARGUMENT(FOnFixSelected, OnFixSelected)
		SLATE_ARGUMENT(TArray<VD::DataPtr>, DataList)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetDataList(TArray<VD::DataPtr>& NewDataList);

private:

	TSharedRef<ITableRow> GenerateRow(VD::DataPtr DataPtr, const TSharedRef<STableViewBase>& Owner);
	void ApplyFilter(const FString& FilterKey);
	void OnSearchKeyChanged(const FText& NewSearchKey);
	bool ContainsFilterKey(const VD::DataPtr& Data);
	FReply OnFixSelectedIssues();

private:
	const FName RowName_AssetName = TEXT("Asset Name");

	TArray<VD::DataPtr> AllDataList;
	TArray<VD::DataPtr> FilteredDataList;

	TSharedPtr<SListView<VD::DataPtr>> ListViewPtr;

	FString CurrentFilterKey;

	const FString PannelDescription = TEXT(
		"Search through all the reported issues by "
		"the validators and if allowed you can select "
		"to resolve issues. Once you have selected the "
		"issues that should be fixed press the fix button.");
	
	FOnFixSelected OnFixSelectedAction;
};