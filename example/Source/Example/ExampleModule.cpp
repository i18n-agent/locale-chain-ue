// Minimal example module demonstrating LocaleChain plugin usage.
//
// On startup this module:
//   1. Calls ULocaleChain::Configure() to load the default 75-entry fallback map
//   2. Inspects the pt-BR fallback chain via GetChain()
//   3. Resolves 3 keys for the current locale (simulating a pt-BR user)
//   4. Logs everything with UE_LOG

#include "ExampleModule.h"
#include "LocaleChain.h"
#include "Internationalization/Internationalization.h"

DEFINE_LOG_CATEGORY_STATIC(LogLocaleChainExample, Log, All);

void FExampleModule::StartupModule()
{
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("=== LocaleChain Example: StartupModule ==="));

	// ---------------------------------------------------------------
	// 1. Configure fallback chains (zero-config: loads all 75 defaults)
	// ---------------------------------------------------------------
	ULocaleChain::Configure();
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("ULocaleChain::Configure() called. IsConfigured = %s"),
		ULocaleChain::IsConfigured() ? TEXT("true") : TEXT("false"));

	// ---------------------------------------------------------------
	// 2. Inspect the pt-BR fallback chain
	// ---------------------------------------------------------------
	TArray<FString> PtBrChain = ULocaleChain::GetChain(TEXT("pt-BR"));
	FString ChainStr;
	for (int32 i = 0; i < PtBrChain.Num(); ++i)
	{
		if (i > 0) ChainStr += TEXT(" -> ");
		ChainStr += PtBrChain[i];
	}
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("pt-BR fallback chain: %s"), *ChainStr);
	// Expected output: "pt-BR fallback chain: pt-PT -> pt"

	// ---------------------------------------------------------------
	// 3. Log current culture for context
	// ---------------------------------------------------------------
	const FString CurrentLocale =
		FInternationalization::Get().GetCurrentCulture()->GetName();
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("Current culture: %s"), *CurrentLocale);

	// ---------------------------------------------------------------
	// 4. Resolve 3 localization keys
	//    These will only return values if you have loaded matching
	//    localization data (e.g., String Tables or .locres files).
	//    Without data loaded, Resolve returns empty -- which is
	//    expected and safe.
	// ---------------------------------------------------------------
	const FString Namespace = TEXT("Game");

	FString Greeting = ULocaleChain::Resolve(TEXT("greeting"), Namespace);
	FString Farewell = ULocaleChain::Resolve(TEXT("farewell"), Namespace);
	FString Welcome  = ULocaleChain::Resolve(TEXT("welcome"),  Namespace);

	UE_LOG(LogLocaleChainExample, Log,
		TEXT("Resolve(\"greeting\", \"%s\") = \"%s\""), *Namespace, *Greeting);
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("Resolve(\"farewell\", \"%s\") = \"%s\""), *Namespace, *Farewell);
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("Resolve(\"welcome\",  \"%s\") = \"%s\""), *Namespace, *Welcome);

	if (Greeting.IsEmpty() && Farewell.IsEmpty() && Welcome.IsEmpty())
	{
		UE_LOG(LogLocaleChainExample, Log,
			TEXT("All keys resolved to empty -- this is expected if no "
			     "localization data (.locres / String Tables) is loaded. "
			     "The fallback chain is configured and ready."));
	}

	UE_LOG(LogLocaleChainExample, Log,
		TEXT("=== LocaleChain Example: Done ==="));
}

void FExampleModule::ShutdownModule()
{
	ULocaleChain::Reset();
	UE_LOG(LogLocaleChainExample, Log,
		TEXT("LocaleChain reset on module shutdown."));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Example, "Example");
