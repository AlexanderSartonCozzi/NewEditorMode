#include "NewEditorTool.h"
#include "UObject/ConstructorHelpers.h"

UNewEditorTool::UNewEditorTool(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UNewEditorTool::ExecuteThis()
{
	UE_LOG(LogTemp, Warning, TEXT("Function is executed"));
}