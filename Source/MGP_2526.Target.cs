// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MGP_2526Target : TargetRules
{
    public MGP_2526Target(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.Add("MGP_2526");
    }
}
