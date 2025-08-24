#pragma once

#include "Widgets/SCompoundWidget.h"
#include "AssetValidationData.h"

DECLARE_DELEGATE(FOnSaveToFile);
DECLARE_DELEGATE(FOnCloseWindow);

class SValidationResultWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SValidationResultWindow) {}
		SLATE_ARGUMENT(double, TimeStamp)
		SLATE_ARGUMENT(FOnSaveToFile, OnSaveToCSV)
		SLATE_ARGUMENT(FOnSaveToFile, OnSaveToJSON)
		SLATE_ARGUMENT(FOnSaveToFile, OnStreamToLog)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	FOnSaveToFile OnSaveToCSV;
	FOnSaveToFile OnSaveToJSON;
	FOnSaveToFile OnStreamToLog;

	double TimeStampValue;

	FReply HandleSaveToCSV();
	FReply HandleSaveToJSON();
	FReply HandleStreamToLog();

	const FText TimeStamp();
};