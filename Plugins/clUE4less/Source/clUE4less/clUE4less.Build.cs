// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class clUE4less : ModuleRules
{
	public clUE4less(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"clUE4less/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"clUE4less/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"clUE4lessLibrary",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		AddThirdPartyPrivateStaticDependencies(Target,
				"clUE4lessLibrary"
				// ... add any third party modules that your module depends on here ...
				);
	}
}
