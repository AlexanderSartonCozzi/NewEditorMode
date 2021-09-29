
using UnrealBuildTool;

public class NewEditorMode : ModuleRules
{
	public NewEditorMode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				"NewEditorMode/Public"
				// ... add public include paths required here ...
			});
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"NewEditorMode/Private",
				// ... add other private include paths required here ...
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"InputCore",
				"LevelEditor",
				"PropertyEditor",
				"Slate",
				"SlateCore",
				"UnrealEd",
			});
	}
}