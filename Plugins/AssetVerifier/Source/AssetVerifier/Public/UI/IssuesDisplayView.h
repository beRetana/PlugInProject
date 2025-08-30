#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"
#include "UI/IssueRowWidget.h"

typedef TArray<TSharedPtr<FAssetValidationData>> DataPtrList;

class SIssueDisplayView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SIssueDisplayView) {}
		SLATE_ARGUMENT(TArray<FAssetValidationData>, DataList)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetDataList(const TArray<FAssetValidationData>& NewDataList);

private:

	void ApplyFilter(const FText& FilterKey);
	void OnSearchKeyChanged(const FText& NewSearchKey);

	DataPtrList AllDataList;
	DataPtrList FilteredDataList;

	TSharedPtr<SListView<ValidationDataRef>> ListViewPtr;

	FText CurrentFilterKey;

	const FString PannelDescription = TEXT(
		"Search through all the reported issues by"
		"the validators and if allowed you can select "
		"to resolve issues. Once you have selected the "
		"issues that should be fixed press the fix button.");
};