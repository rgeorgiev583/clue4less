// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "clUE4lessPrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"
#if PLATFORM_WINDOWS
    #include "ExampleLibrary.h"
#endif // PLATFORM_WINDOWS

#define LOCTEXT_NAMESPACE "FclUE4lessModule"

void FclUE4lessModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("clUE4less")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/clUE4lessLibrary/Win64/ExampleLibrary.dll"));

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		ExampleLibraryFunction();
	}
	else
#endif // PLATFORM_WINDOWS
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FclUE4lessModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FclUE4lessModule, clUE4less)