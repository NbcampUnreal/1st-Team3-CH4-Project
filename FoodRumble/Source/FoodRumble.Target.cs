

using UnrealBuildTool;
using System.Collections.Generic;

public class FoodRumbleTarget : TargetRules
{
	public FoodRumbleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "FoodRumble" } );
	}
}
