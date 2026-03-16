// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

using UnrealBuildTool;

public class LocaleChain : ModuleRules
{
	public LocaleChain(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine"
		});
	}
}
