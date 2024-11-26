// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheForgottenTrialsTarget : TargetRules
{
	public TheForgottenTrialsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("TheForgottenTrials");

        GlobalDefinitions.Add("USE_LOGGING_IN_SHIPPING=1");
        GlobalDefinitions.Add("UE_WITH_CHEAT_MANAGER=1");
		GlobalDefinitions.Add("ALLOW_CONSOLE=1");

		bUseLoggingInShipping = true;
		bOverrideBuildEnvironment = true;
    }
}
