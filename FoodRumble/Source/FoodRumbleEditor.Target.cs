

using UnrealBuildTool;
using System.Collections.Generic;

public class FoodRumbleEditorTarget : TargetRules
{
	public FoodRumbleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "FoodRumble" } );
	}
}
