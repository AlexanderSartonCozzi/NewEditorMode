// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "NewEdMode.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetThumbnail.h"
#include "Toolkits/BaseToolkit.h"
#include "Editor.h"

class IDetailsView;
class SNewEditor;
class SErrorText;
struct FPropertyAndParent;

class FNewEdModeToolkit : public FModeToolkit
{
public:	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FNewEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override;
	

private:
	/** Geometry tools widget */
	TSharedPtr<SNewEditor> NewEditorWidgets;
};

/**
* Slate widgets for the New Editor Mode
*/
class SNewEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNewEditor) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedRef<FNewEdModeToolkit> InParentToolkit);

	void RefreshDetailPanel();
	
protected:

	class FNewEdMode* GetEditorMode() const;

	FText GetErrorText() const;

	bool GetNewEditorIsEnabled() const;

	bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;

	TSharedPtr<SErrorText> Error;

	TSharedPtr<IDetailsView> DetailsPanel;
};
