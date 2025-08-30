#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"

DECLARE_DELEGATE(FOnSaveToFile);
DECLARE_DELEGATE(FOnFixIssues);

class SValidationResultWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SValidationResultWindow) {}
		SLATE_ARGUMENT(double, TimeStamp)
		SLATE_ARGUMENT(uint32, ErrorCountNum)
		SLATE_ARGUMENT(FOnSaveToFile, OnSaveToCSV)
		SLATE_ARGUMENT(FOnSaveToFile, OnSaveToJSON)
		SLATE_ARGUMENT(FOnSaveToFile, OnStreamToLog)
		SLATE_ARGUMENT(FOnFixIssues, OnFixIssues)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	FOnSaveToFile OnSaveToCSV;
	FOnSaveToFile OnSaveToJSON;
	FOnSaveToFile OnStreamToLog;
	FOnFixIssues OnFixIssues;

	double TimeStampValue{0};
	int32 ErrorCountValue{0};

	FReply HandleSaveToCSV();
	FReply HandleSaveToJSON();
	FReply HandleStreamToLog();
	FReply HandleIssuesWindow();

	const EVisibility GetVisibility();

	const FText TimeStamp();
	const FText ErrorCount();
};