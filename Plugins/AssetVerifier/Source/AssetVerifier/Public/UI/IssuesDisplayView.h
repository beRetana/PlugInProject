#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"
#include "UI/IssueRowWidget.h"

class SIssueDisplayView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SIssueDisplayView) {}
		SLATE_ARGUMENT(TArray<DataPtr>, DataList)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetDataList(const TArray<FAssetValidationData>& NewDataList);

private:

	TSharedRef<ITableRow> GenerateRow(DataPtr DataPtr, const TSharedRef<STableViewBase>& Owner);
	void ApplyFilter(const FString& FilterKey);
	void OnSearchKeyChanged(const FText& NewSearchKey);
	bool ContainsFilterKey(const DataPtr& Data);

	TArray<DataPtr> AllDataList;
	TArray<DataPtr> FilteredDataList;

	TSharedPtr<SListView<DataPtr>> ListViewPtr;

	FString CurrentFilterKey;

	const FString PannelDescription = TEXT(
		"Search through all the reported issues by"
		"the validators and if allowed you can select "
		"to resolve issues. Once you have selected the "
		"issues that should be fixed press the fix button.");
};