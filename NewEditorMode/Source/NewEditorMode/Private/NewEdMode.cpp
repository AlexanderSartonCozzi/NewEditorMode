// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NewEdMode.h"
#include "SNewEditor.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FNewEdMode::EM_NewEdModeId = TEXT("EM_NewEdMode");

FNewEdMode::FNewEdMode()
{
	UISettings = NewObject<UNewEditorTool>(GetTransientPackage(), TEXT("NewUISettings"), RF_Transactional);
	UISettings->SetParent(this);
}

FNewEdMode::~FNewEdMode()
{

}

void FNewEdMode::AddReferencedObjects(FReferenceCollector & Collector)
{
	// Call parent implementation
	FEdMode::AddReferencedObjects(Collector);

	Collector.AddReferencedObject(UISettings);
}

void FNewEdMode::Enter()
{
	FEdMode::Enter();
	
	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FNewEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FNewEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FNewEdMode::UsesToolkits() const
{
	return true;
}




