// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SNewEditor.h"
#include "NewEdMode.h"
#include "NewEditorTool.h"
#include "NewEditorToolCustomization.h"
#include "Engine/Selection.h"

#include "PropertyEditorModule.h"
#include "SlateOptMacros.h"

#include "IDetailsView.h"
#include "IIntroTutorials.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Notifications/SErrorText.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FNewEditorTool"


void FNewEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	FNewEdMode* NewEdMode = GetEditorMode();

	NewEditorWidgets = SNew(SNewEditor, SharedThis(this));

	FModeToolkit::Init(InitToolkitHost);
}

FName FNewEdModeToolkit::GetToolkitFName() const
{
	return FName("NewEditor");
}

FText FNewEdModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("Toolkitname", "New Editor");
}

FNewEdMode* FNewEdModeToolkit::GetEditorMode() const
{
	return (FNewEdMode*)GLevelEditorModeTools().GetActiveMode(FNewEdMode::EM_NewEdModeId);
}

TSharedPtr<SWidget> FNewEdModeToolkit::GetInlineContent() const
{
	return NewEditorWidgets;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SNewEditor::Construct(const FArguments& InArgs, TSharedRef<FNewEdModeToolkit> InParentToolkit)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout("NewEditorTool", FOnGetDetailCustomizationInstance::CreateStatic(&FNewEditorToolCustomization::MakeInstance));
	PropertyEditorModule.NotifyCustomizationModuleChanged();

	FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);
	
	DetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsPanel->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateSP(this, &SNewEditor::GetIsPropertyVisible));
	
	FNewEdMode* NewEdMode = GetEditorMode();
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(0)
		[
			SNew(SVerticalBox)
			.IsEnabled(this, &SNewEditor::GetNewEditorIsEnabled)
			+ SVerticalBox::Slot()
			.Padding(0)
			[
				DetailsPanel.ToSharedRef()
			]
		]
	];

	RefreshDetailPanel();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FNewEdMode* SNewEditor::GetEditorMode() const
{
	return (FNewEdMode*)GLevelEditorModeTools().GetActiveMode(FNewEdMode::EM_NewEdModeId);
}

FText SNewEditor::GetErrorText() const
{
	FNewEdMode* NewEdMode = GetEditorMode();

	return FText::GetEmpty();
}

bool SNewEditor::GetNewEditorIsEnabled() const
{
	FNewEdMode* NewEdMode = GetEditorMode();
	if (NewEdMode)
	{
		return true;
	}
	return false;
}

bool SNewEditor::GetIsPropertyVisible(const FPropertyAndParent & PropertyAndParent) const
{
	return true;
}

void SNewEditor::RefreshDetailPanel()
{
	FNewEdMode* NewEdMode = GetEditorMode();
	if (NewEdMode)
	{
		// Refresh details panel
		DetailsPanel->SetObject(NewEdMode->UISettings, true);
	}
}
#undef LOCTEXT_NAMESPACE