#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "NewEdMode.h"
#include "NewEditorTool.generated.h"

class FNewEdMode;

UCLASS()
class UNewEditorTool : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	FNewEdMode* ParentMode;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	UMaterial* Material;

	UPROPERTY(EditAnywhere, Category = "Settings")
		float testfloat = 10;
	UPROPERTY(EditAnywhere, Category = "Settings")
		bool testbool = true;
	UPROPERTY(EditAnywhere, Category = "Settings")
		int testint = 8;
	UPROPERTY(EditAnywhere, Category = "Settings")
		FString teststring = "this is a string";

	UFUNCTION(Exec)
	void ExecuteThis();

	void SetParent(FNewEdMode* NewParent)
	{
		ParentMode = NewParent;
	}
};