// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NewEditorModeModule.h"
#include "NewEdMode.h"
#include "NewEditorToolCustomization.h"
#include "NewEditorTool.h"

#include "PropertyEditorModule.h"
#include "Interfaces/IPluginManager.h"

#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "EditorStyleSet.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "FNewEditorModeModule"
#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FNewEditorModeModule::InContent( RelativePath, ".png" ), __VA_ARGS__ )

FString FNewEditorModeModule::InContent(const FString & RelativePath, const ANSICHAR * Extension)
{
	static FString ContentDir = FPaths::ProjectPluginsDir() / TEXT("NewEditorMode/Content/Slate");
	return (ContentDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FNewEditorModeModule::StyleSet = nullptr;
TSharedPtr< class ISlateStyle > FNewEditorModeModule::Get() { return StyleSet; }

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FNewEditorModeModule::Initialize()
{
	// Const icon sizes
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("NewEditorMode/Content/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	
	StyleSet->Set("LevelEditor.NewEditorMode", new IMAGE_PLUGIN_BRUSH("Icons/New_editor_icon_40x", Icon40x40));
	StyleSet->Set("LevelEditor.NewEditorMode.Small", new IMAGE_PLUGIN_BRUSH("Icons/New_editor_icon_40x", Icon20x20));
	StyleSet->Set("LevelEditor.NewEditorMode.Selected", new IMAGE_PLUGIN_BRUSH("Icons/New_editor_icon_40x", Icon40x40));
	StyleSet->Set("LevelEditor.NewEditorMode.Selected.Small", new IMAGE_PLUGIN_BRUSH("Icons/New_editor_icon_40x", Icon20x20));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_PLUGIN_BRUSH

FName FNewEditorModeModule::GetStyleSetName()
{
	static FName StyleName(TEXT("NewEditorMode"));
	return StyleName;
}

void FNewEditorModeModule::StartupModule()
{
	//Initialize styleset
	Initialize();

	//register mode
	FEditorModeRegistry::Get().RegisterMode<FNewEdMode>(
		FNewEdMode::EM_NewEdModeId,
		LOCTEXT("NewEditorModeEdModeName", "NewEditorModeEdMode"),
		FSlateIcon(GetStyleSetName(), "LevelEditor.NewEditorMode", "LevelEditor.NewEditorMode.Small"),
		true
		);
}

void FNewEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FNewEdMode::EM_NewEdModeId);

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNewEditorModeModule, NewEditorMode)