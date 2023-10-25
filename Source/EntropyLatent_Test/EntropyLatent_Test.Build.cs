using UnrealBuildTool;

public class EntropyLatent_Test : ModuleRules
{
    public EntropyLatent_Test(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EntropyLatent",
                "UE5Coro"
            }
        );
    }
}