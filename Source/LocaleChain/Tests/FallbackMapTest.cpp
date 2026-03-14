// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

#include "Misc/AutomationTest.h"
#include "FallbackMap.h"

// -----------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------

/**
 * Counts entries whose key starts with the given prefix.
 */
static int32 CountGroup(
	const TMap<FString, TArray<FString>>& Map,
	const FString& Prefix)
{
	int32 Count = 0;
	for (const auto& Pair : Map)
	{
		if (Pair.Key.StartsWith(Prefix))
		{
			++Count;
		}
	}
	return Count;
}

/**
 * Checks whether an array contains a specific element.
 */
static bool ArrayContains(const TArray<FString>& Arr, const FString& Value)
{
	return Arr.Contains(Value);
}

// =====================================================================
// Language Group Presence
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FChineseTraditionalGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.ChineseTraditional",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FChineseTraditionalGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("zh-Hant-HK present"), Defaults.Contains(TEXT("zh-Hant-HK")));
	TestTrue(TEXT("zh-Hant-MO present"), Defaults.Contains(TEXT("zh-Hant-MO")));
	TestTrue(TEXT("zh-Hant-TW present"), Defaults.Contains(TEXT("zh-Hant-TW")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FChineseSimplifiedGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.ChineseSimplified",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FChineseSimplifiedGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("zh-Hans-SG present"), Defaults.Contains(TEXT("zh-Hans-SG")));
	TestTrue(TEXT("zh-Hans-MY present"), Defaults.Contains(TEXT("zh-Hans-MY")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPortugueseGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Portuguese",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPortugueseGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("pt-BR present"), Defaults.Contains(TEXT("pt-BR")));
	TestTrue(TEXT("pt-PT present"), Defaults.Contains(TEXT("pt-PT")));
	TestTrue(TEXT("pt-AO present"), Defaults.Contains(TEXT("pt-AO")));
	TestTrue(TEXT("pt-MZ present"), Defaults.Contains(TEXT("pt-MZ")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FSpanishGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Spanish",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSpanishGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("es-419 present"), Defaults.Contains(TEXT("es-419")));
	TestTrue(TEXT("es-MX present"),  Defaults.Contains(TEXT("es-MX")));
	TestTrue(TEXT("es-AR present"),  Defaults.Contains(TEXT("es-AR")));
	TestTrue(TEXT("es-CO present"),  Defaults.Contains(TEXT("es-CO")));
	TestTrue(TEXT("es-CL present"),  Defaults.Contains(TEXT("es-CL")));
	TestTrue(TEXT("es-PE present"),  Defaults.Contains(TEXT("es-PE")));
	TestTrue(TEXT("es-VE present"),  Defaults.Contains(TEXT("es-VE")));
	TestTrue(TEXT("es-EC present"),  Defaults.Contains(TEXT("es-EC")));
	TestTrue(TEXT("es-GT present"),  Defaults.Contains(TEXT("es-GT")));
	TestTrue(TEXT("es-CU present"),  Defaults.Contains(TEXT("es-CU")));
	TestTrue(TEXT("es-BO present"),  Defaults.Contains(TEXT("es-BO")));
	TestTrue(TEXT("es-DO present"),  Defaults.Contains(TEXT("es-DO")));
	TestTrue(TEXT("es-HN present"),  Defaults.Contains(TEXT("es-HN")));
	TestTrue(TEXT("es-PY present"),  Defaults.Contains(TEXT("es-PY")));
	TestTrue(TEXT("es-SV present"),  Defaults.Contains(TEXT("es-SV")));
	TestTrue(TEXT("es-NI present"),  Defaults.Contains(TEXT("es-NI")));
	TestTrue(TEXT("es-CR present"),  Defaults.Contains(TEXT("es-CR")));
	TestTrue(TEXT("es-PA present"),  Defaults.Contains(TEXT("es-PA")));
	TestTrue(TEXT("es-UY present"),  Defaults.Contains(TEXT("es-UY")));
	TestTrue(TEXT("es-PR present"),  Defaults.Contains(TEXT("es-PR")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FFrenchGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.French",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFrenchGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("fr-CA present"), Defaults.Contains(TEXT("fr-CA")));
	TestTrue(TEXT("fr-BE present"), Defaults.Contains(TEXT("fr-BE")));
	TestTrue(TEXT("fr-CH present"), Defaults.Contains(TEXT("fr-CH")));
	TestTrue(TEXT("fr-LU present"), Defaults.Contains(TEXT("fr-LU")));
	TestTrue(TEXT("fr-MC present"), Defaults.Contains(TEXT("fr-MC")));
	TestTrue(TEXT("fr-SN present"), Defaults.Contains(TEXT("fr-SN")));
	TestTrue(TEXT("fr-CI present"), Defaults.Contains(TEXT("fr-CI")));
	TestTrue(TEXT("fr-ML present"), Defaults.Contains(TEXT("fr-ML")));
	TestTrue(TEXT("fr-CM present"), Defaults.Contains(TEXT("fr-CM")));
	TestTrue(TEXT("fr-MG present"), Defaults.Contains(TEXT("fr-MG")));
	TestTrue(TEXT("fr-CD present"), Defaults.Contains(TEXT("fr-CD")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGermanGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.German",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGermanGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("de-AT present"), Defaults.Contains(TEXT("de-AT")));
	TestTrue(TEXT("de-CH present"), Defaults.Contains(TEXT("de-CH")));
	TestTrue(TEXT("de-LU present"), Defaults.Contains(TEXT("de-LU")));
	TestTrue(TEXT("de-LI present"), Defaults.Contains(TEXT("de-LI")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FItalianGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Italian",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FItalianGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("it-CH present"), Defaults.Contains(TEXT("it-CH")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FDutchGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Dutch",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDutchGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("nl-BE present"), Defaults.Contains(TEXT("nl-BE")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FEnglishGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.English",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FEnglishGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("en-GB present"), Defaults.Contains(TEXT("en-GB")));
	TestTrue(TEXT("en-AU present"), Defaults.Contains(TEXT("en-AU")));
	TestTrue(TEXT("en-NZ present"), Defaults.Contains(TEXT("en-NZ")));
	TestTrue(TEXT("en-IN present"), Defaults.Contains(TEXT("en-IN")));
	TestTrue(TEXT("en-CA present"), Defaults.Contains(TEXT("en-CA")));
	TestTrue(TEXT("en-ZA present"), Defaults.Contains(TEXT("en-ZA")));
	TestTrue(TEXT("en-IE present"), Defaults.Contains(TEXT("en-IE")));
	TestTrue(TEXT("en-SG present"), Defaults.Contains(TEXT("en-SG")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FArabicGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Arabic",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArabicGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("ar-SA present"), Defaults.Contains(TEXT("ar-SA")));
	TestTrue(TEXT("ar-EG present"), Defaults.Contains(TEXT("ar-EG")));
	TestTrue(TEXT("ar-AE present"), Defaults.Contains(TEXT("ar-AE")));
	TestTrue(TEXT("ar-MA present"), Defaults.Contains(TEXT("ar-MA")));
	TestTrue(TEXT("ar-DZ present"), Defaults.Contains(TEXT("ar-DZ")));
	TestTrue(TEXT("ar-IQ present"), Defaults.Contains(TEXT("ar-IQ")));
	TestTrue(TEXT("ar-KW present"), Defaults.Contains(TEXT("ar-KW")));
	TestTrue(TEXT("ar-QA present"), Defaults.Contains(TEXT("ar-QA")));
	TestTrue(TEXT("ar-BH present"), Defaults.Contains(TEXT("ar-BH")));
	TestTrue(TEXT("ar-OM present"), Defaults.Contains(TEXT("ar-OM")));
	TestTrue(TEXT("ar-JO present"), Defaults.Contains(TEXT("ar-JO")));
	TestTrue(TEXT("ar-LB present"), Defaults.Contains(TEXT("ar-LB")));
	TestTrue(TEXT("ar-TN present"), Defaults.Contains(TEXT("ar-TN")));
	TestTrue(TEXT("ar-LY present"), Defaults.Contains(TEXT("ar-LY")));
	TestTrue(TEXT("ar-SD present"), Defaults.Contains(TEXT("ar-SD")));
	TestTrue(TEXT("ar-YE present"), Defaults.Contains(TEXT("ar-YE")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNorwegianGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Norwegian",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNorwegianGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("nb present"), Defaults.Contains(TEXT("nb")));
	TestTrue(TEXT("nn present"), Defaults.Contains(TEXT("nn")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMalayGroupPresent,
	"LocaleChain.FallbackMap.GroupPresence.Malay",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMalayGroupPresent::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestTrue(TEXT("ms-MY present"), Defaults.Contains(TEXT("ms-MY")));
	TestTrue(TEXT("ms-SG present"), Defaults.Contains(TEXT("ms-SG")));
	TestTrue(TEXT("ms-BN present"), Defaults.Contains(TEXT("ms-BN")));
	return true;
}

// =====================================================================
// Chain Integrity
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNoEmptyChains,
	"LocaleChain.FallbackMap.ChainIntegrity.NoEmptyChains",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNoEmptyChains::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	for (const auto& Pair : Defaults)
	{
		TestTrue(
			*FString::Printf(TEXT("Chain for %s is not empty"), *Pair.Key),
			Pair.Value.Num() > 0);
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNoSelfReferences,
	"LocaleChain.FallbackMap.ChainIntegrity.NoSelfReferences",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNoSelfReferences::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	for (const auto& Pair : Defaults)
	{
		TestFalse(
			*FString::Printf(TEXT("%s does not contain itself in its chain"), *Pair.Key),
			ArrayContains(Pair.Value, Pair.Key));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNoCyclicReferences,
	"LocaleChain.FallbackMap.ChainIntegrity.NoCyclicReferences",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNoCyclicReferences::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	for (const auto& Pair : Defaults)
	{
		// Check direct self-reference
		TestFalse(
			*FString::Printf(TEXT("%s has no direct cycle"), *Pair.Key),
			ArrayContains(Pair.Value, Pair.Key));

		// Check one-level indirect cycle
		for (const FString& Fallback : Pair.Value)
		{
			const TArray<FString>* FallbackChain = Defaults.Find(Fallback);
			if (FallbackChain != nullptr)
			{
				TestFalse(
					*FString::Printf(
						TEXT("Chain for %s does not reference %s (indirect cycle)"),
						*Fallback, *Pair.Key),
					ArrayContains(*FallbackChain, Pair.Key));
			}
		}
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNoDuplicateEntriesInChains,
	"LocaleChain.FallbackMap.ChainIntegrity.NoDuplicateEntries",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNoDuplicateEntriesInChains::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	for (const auto& Pair : Defaults)
	{
		TSet<FString> Seen;
		bool bHasDuplicate = false;
		for (const FString& Entry : Pair.Value)
		{
			if (Seen.Contains(Entry))
			{
				bHasDuplicate = true;
				break;
			}
			Seen.Add(Entry);
		}
		TestFalse(
			*FString::Printf(TEXT("Chain for %s has no duplicate entries"), *Pair.Key),
			bHasDuplicate);
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FTotalLocaleCount,
	"LocaleChain.FallbackMap.ChainIntegrity.TotalLocaleCount",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FTotalLocaleCount::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TestEqual(TEXT("Total locale count is 75"), Defaults.Num(), 75);
	return true;
}

// =====================================================================
// Group Chain Counts
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGroupCounts,
	"LocaleChain.FallbackMap.GroupCounts",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGroupCounts::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	TestEqual(TEXT("Chinese Traditional has 3 locales"), CountGroup(Defaults, TEXT("zh-Hant")), 3);
	TestEqual(TEXT("Chinese Simplified has 2 locales"),  CountGroup(Defaults, TEXT("zh-Hans")), 2);
	TestEqual(TEXT("Portuguese has 4 locales"),          CountGroup(Defaults, TEXT("pt")),      4);
	TestEqual(TEXT("Spanish has 20 locales"),            CountGroup(Defaults, TEXT("es")),      20);
	TestEqual(TEXT("French has 11 locales"),             CountGroup(Defaults, TEXT("fr")),      11);
	TestEqual(TEXT("German has 4 locales"),              CountGroup(Defaults, TEXT("de")),      4);
	TestEqual(TEXT("Italian has 1 locale"),              CountGroup(Defaults, TEXT("it")),      1);
	TestEqual(TEXT("Dutch has 1 locale"),                CountGroup(Defaults, TEXT("nl")),      1);
	TestEqual(TEXT("English has 8 locales"),             CountGroup(Defaults, TEXT("en")),      8);
	TestEqual(TEXT("Arabic has 16 locales"),             CountGroup(Defaults, TEXT("ar")),      16);
	TestEqual(TEXT("Malay has 3 locales"),               CountGroup(Defaults, TEXT("ms")),      3);

	// Norwegian uses nb and nn — no common prefix, count manually.
	int32 NorwegianCount = 0;
	if (Defaults.Contains(TEXT("nb"))) ++NorwegianCount;
	if (Defaults.Contains(TEXT("nn"))) ++NorwegianCount;
	TestEqual(TEXT("Norwegian has 2 locales"), NorwegianCount, 2);

	return true;
}

// =====================================================================
// Specific Chain Values
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPortugueseChainValues,
	"LocaleChain.FallbackMap.ChainValues.Portuguese",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPortugueseChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedPtBr = {TEXT("pt-PT"), TEXT("pt")};
	TestEqual(TEXT("pt-BR chain"), *Defaults.Find(TEXT("pt-BR")), ExpectedPtBr);

	const TArray<FString> ExpectedPtPt = {TEXT("pt")};
	TestEqual(TEXT("pt-PT chain"), *Defaults.Find(TEXT("pt-PT")), ExpectedPtPt);

	const TArray<FString> ExpectedPtAo = {TEXT("pt-PT"), TEXT("pt")};
	TestEqual(TEXT("pt-AO chain"), *Defaults.Find(TEXT("pt-AO")), ExpectedPtAo);

	const TArray<FString> ExpectedPtMz = {TEXT("pt-PT"), TEXT("pt")};
	TestEqual(TEXT("pt-MZ chain"), *Defaults.Find(TEXT("pt-MZ")), ExpectedPtMz);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FChineseChainValues,
	"LocaleChain.FallbackMap.ChainValues.Chinese",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FChineseChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedHantHk = {TEXT("zh-Hant-TW"), TEXT("zh-Hant")};
	TestEqual(TEXT("zh-Hant-HK chain"), *Defaults.Find(TEXT("zh-Hant-HK")), ExpectedHantHk);

	const TArray<FString> ExpectedHantMo = {TEXT("zh-Hant-HK"), TEXT("zh-Hant-TW"), TEXT("zh-Hant")};
	TestEqual(TEXT("zh-Hant-MO chain"), *Defaults.Find(TEXT("zh-Hant-MO")), ExpectedHantMo);

	const TArray<FString> ExpectedHantTw = {TEXT("zh-Hant")};
	TestEqual(TEXT("zh-Hant-TW chain"), *Defaults.Find(TEXT("zh-Hant-TW")), ExpectedHantTw);

	const TArray<FString> ExpectedHansSg = {TEXT("zh-Hans")};
	TestEqual(TEXT("zh-Hans-SG chain"), *Defaults.Find(TEXT("zh-Hans-SG")), ExpectedHansSg);

	const TArray<FString> ExpectedHansMy = {TEXT("zh-Hans")};
	TestEqual(TEXT("zh-Hans-MY chain"), *Defaults.Find(TEXT("zh-Hans-MY")), ExpectedHansMy);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FEnglishChainValues,
	"LocaleChain.FallbackMap.ChainValues.English",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FEnglishChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedGb = {TEXT("en")};
	TestEqual(TEXT("en-GB chain"), *Defaults.Find(TEXT("en-GB")), ExpectedGb);

	const TArray<FString> ExpectedAu = {TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-AU chain"), *Defaults.Find(TEXT("en-AU")), ExpectedAu);

	const TArray<FString> ExpectedNz = {TEXT("en-AU"), TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-NZ chain"), *Defaults.Find(TEXT("en-NZ")), ExpectedNz);

	const TArray<FString> ExpectedIn = {TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-IN chain"), *Defaults.Find(TEXT("en-IN")), ExpectedIn);

	const TArray<FString> ExpectedCa = {TEXT("en")};
	TestEqual(TEXT("en-CA chain"), *Defaults.Find(TEXT("en-CA")), ExpectedCa);

	const TArray<FString> ExpectedZa = {TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-ZA chain"), *Defaults.Find(TEXT("en-ZA")), ExpectedZa);

	const TArray<FString> ExpectedIe = {TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-IE chain"), *Defaults.Find(TEXT("en-IE")), ExpectedIe);

	const TArray<FString> ExpectedSg = {TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-SG chain"), *Defaults.Find(TEXT("en-SG")), ExpectedSg);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FSpanishChainValues,
	"LocaleChain.FallbackMap.ChainValues.Spanish",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSpanishChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedEs419 = {TEXT("es")};
	TestEqual(TEXT("es-419 chain"), *Defaults.Find(TEXT("es-419")), ExpectedEs419);

	// All Latin American locales should chain to [es-419, es].
	const TArray<FString> ExpectedLatinAm = {TEXT("es-419"), TEXT("es")};
	const TArray<FString> LatinAmericanLocales = {
		TEXT("es-MX"),  TEXT("es-AR"),  TEXT("es-CO"),  TEXT("es-CL"),
		TEXT("es-PE"),  TEXT("es-VE"),  TEXT("es-EC"),  TEXT("es-GT"),
		TEXT("es-CU"),  TEXT("es-BO"),  TEXT("es-DO"),  TEXT("es-HN"),
		TEXT("es-PY"),  TEXT("es-SV"),  TEXT("es-NI"),  TEXT("es-CR"),
		TEXT("es-PA"),  TEXT("es-UY"),  TEXT("es-PR")
	};
	for (const FString& Locale : LatinAmericanLocales)
	{
		TestEqual(
			*FString::Printf(TEXT("%s chain"), *Locale),
			*Defaults.Find(Locale),
			ExpectedLatinAm);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FFrenchChainValues,
	"LocaleChain.FallbackMap.ChainValues.French",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFrenchChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedFr = {TEXT("fr")};
	const TArray<FString> FrenchLocales = {
		TEXT("fr-CA"), TEXT("fr-BE"), TEXT("fr-CH"), TEXT("fr-LU"), TEXT("fr-MC"),
		TEXT("fr-SN"), TEXT("fr-CI"), TEXT("fr-ML"), TEXT("fr-CM"), TEXT("fr-MG"),
		TEXT("fr-CD")
	};
	for (const FString& Locale : FrenchLocales)
	{
		TestEqual(
			*FString::Printf(TEXT("%s chain"), *Locale),
			*Defaults.Find(Locale),
			ExpectedFr);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGermanChainValues,
	"LocaleChain.FallbackMap.ChainValues.German",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGermanChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedDe = {TEXT("de")};
	const TArray<FString> GermanLocales = {
		TEXT("de-AT"), TEXT("de-CH"), TEXT("de-LU"), TEXT("de-LI")
	};
	for (const FString& Locale : GermanLocales)
	{
		TestEqual(
			*FString::Printf(TEXT("%s chain"), *Locale),
			*Defaults.Find(Locale),
			ExpectedDe);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FItalianChainValue,
	"LocaleChain.FallbackMap.ChainValues.Italian",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FItalianChainValue::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	const TArray<FString> Expected = {TEXT("it")};
	TestEqual(TEXT("it-CH chain"), *Defaults.Find(TEXT("it-CH")), Expected);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FDutchChainValue,
	"LocaleChain.FallbackMap.ChainValues.Dutch",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDutchChainValue::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	const TArray<FString> Expected = {TEXT("nl")};
	TestEqual(TEXT("nl-BE chain"), *Defaults.Find(TEXT("nl-BE")), Expected);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNorwegianChainValues,
	"LocaleChain.FallbackMap.ChainValues.Norwegian",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNorwegianChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedNb = {TEXT("no")};
	TestEqual(TEXT("nb chain"), *Defaults.Find(TEXT("nb")), ExpectedNb);

	const TArray<FString> ExpectedNn = {TEXT("nb"), TEXT("no")};
	TestEqual(TEXT("nn chain"), *Defaults.Find(TEXT("nn")), ExpectedNn);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FArabicChainValues,
	"LocaleChain.FallbackMap.ChainValues.Arabic",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArabicChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedAr = {TEXT("ar")};
	const TArray<FString> ArabicLocales = {
		TEXT("ar-SA"), TEXT("ar-EG"), TEXT("ar-AE"), TEXT("ar-MA"),
		TEXT("ar-DZ"), TEXT("ar-IQ"), TEXT("ar-KW"), TEXT("ar-QA"),
		TEXT("ar-BH"), TEXT("ar-OM"), TEXT("ar-JO"), TEXT("ar-LB"),
		TEXT("ar-TN"), TEXT("ar-LY"), TEXT("ar-SD"), TEXT("ar-YE")
	};
	for (const FString& Locale : ArabicLocales)
	{
		TestEqual(
			*FString::Printf(TEXT("%s chain"), *Locale),
			*Defaults.Find(Locale),
			ExpectedAr);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMalayChainValues,
	"LocaleChain.FallbackMap.ChainValues.Malay",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMalayChainValues::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	const TArray<FString> ExpectedMs = {TEXT("ms")};
	TestEqual(TEXT("ms-MY chain"), *Defaults.Find(TEXT("ms-MY")), ExpectedMs);
	TestEqual(TEXT("ms-SG chain"), *Defaults.Find(TEXT("ms-SG")), ExpectedMs);
	TestEqual(TEXT("ms-BN chain"), *Defaults.Find(TEXT("ms-BN")), ExpectedMs);

	return true;
}

// =====================================================================
// Merge: Overrides Replace
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeOverridesReplace,
	"LocaleChain.FallbackMap.Merge.OverridesReplace",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeOverridesReplace::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	// Override replaces pt-BR chain
	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("pt-BR"), {TEXT("pt")});

	auto Merged = FFallbackMap::Merge(Defaults, Overrides);

	const TArray<FString> ExpectedPtBr = {TEXT("pt")};
	TestEqual(TEXT("Override replaces pt-BR chain"), *Merged.Find(TEXT("pt-BR")), ExpectedPtBr);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeOverridesReplaceDifferentLength,
	"LocaleChain.FallbackMap.Merge.OverridesReplaceDifferentLength",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeOverridesReplaceDifferentLength::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> Base;
	Base.Add(TEXT("es-MX"), {TEXT("es-419"), TEXT("es")});

	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("es-MX"), {TEXT("es-419"), TEXT("es-LA"), TEXT("es")});

	auto Merged = FFallbackMap::Merge(Base, Overrides);

	const TArray<FString> Expected = {TEXT("es-419"), TEXT("es-LA"), TEXT("es")};
	TestEqual(TEXT("Override can change chain length"), *Merged.Find(TEXT("es-MX")), Expected);

	return true;
}

// =====================================================================
// Merge: New Locales Added
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeAddsNewLocale,
	"LocaleChain.FallbackMap.Merge.AddsNewLocale",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeAddsNewLocale::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> Base;
	Base.Add(TEXT("pt-BR"), {TEXT("pt-PT"), TEXT("pt")});

	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("ja-JP"), {TEXT("ja")});

	auto Merged = FFallbackMap::Merge(Base, Overrides);

	TestTrue(TEXT("New locale ja-JP added by merge"), Merged.Contains(TEXT("ja-JP")));
	const TArray<FString> Expected = {TEXT("ja")};
	TestEqual(TEXT("New locale ja-JP has correct chain"), *Merged.Find(TEXT("ja-JP")), Expected);
	TestTrue(TEXT("Existing locale pt-BR still present"), Merged.Contains(TEXT("pt-BR")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeAddsMultipleNewLocales,
	"LocaleChain.FallbackMap.Merge.AddsMultipleNewLocales",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeAddsMultipleNewLocales::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> Base;
	Base.Add(TEXT("en-GB"), {TEXT("en")});

	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("ko-KR"), {TEXT("ko")});
	Overrides.Add(TEXT("ja-JP"), {TEXT("ja")});

	auto Merged = FFallbackMap::Merge(Base, Overrides);

	TestEqual(TEXT("Merged map has 3 entries"), Merged.Num(), 3);
	TestTrue(TEXT("ko-KR added"), Merged.Contains(TEXT("ko-KR")));
	TestTrue(TEXT("ja-JP added"), Merged.Contains(TEXT("ja-JP")));
	TestTrue(TEXT("en-GB preserved"), Merged.Contains(TEXT("en-GB")));

	return true;
}

// =====================================================================
// Merge: Defaults Preserved
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergePreservesNonMatchingDefaults,
	"LocaleChain.FallbackMap.Merge.PreservesNonMatchingDefaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergePreservesNonMatchingDefaults::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();

	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("pt-BR"), {TEXT("pt")});

	auto Merged = FFallbackMap::Merge(Defaults, Overrides);

	// Other chains remain unchanged
	const TArray<FString> ExpectedPtPt = {TEXT("pt")};
	TestEqual(TEXT("pt-PT preserved"), *Merged.Find(TEXT("pt-PT")), ExpectedPtPt);

	const TArray<FString> ExpectedEsMx = {TEXT("es-419"), TEXT("es")};
	TestEqual(TEXT("es-MX preserved"), *Merged.Find(TEXT("es-MX")), ExpectedEsMx);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergePreservesAllWithEmptyOverrides,
	"LocaleChain.FallbackMap.Merge.PreservesAllWithEmptyOverrides",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergePreservesAllWithEmptyOverrides::RunTest(const FString& Parameters)
{
	const auto& Defaults = FFallbackMap::GetDefaults();
	TMap<FString, TArray<FString>> EmptyOverrides;

	auto Merged = FFallbackMap::Merge(Defaults, EmptyOverrides);

	TestEqual(TEXT("Empty overrides preserves all defaults"),
		Merged.Num(), Defaults.Num());

	for (const auto& Pair : Defaults)
	{
		TestTrue(
			*FString::Printf(TEXT("Locale %s still present after empty merge"), *Pair.Key),
			Merged.Contains(Pair.Key));
		TestEqual(
			*FString::Printf(TEXT("Locale %s chain unchanged"), *Pair.Key),
			*Merged.Find(Pair.Key),
			Pair.Value);
	}

	return true;
}

// =====================================================================
// Merge: Edge Cases
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeEmptyBaseWithOverrides,
	"LocaleChain.FallbackMap.Merge.EmptyBaseWithOverrides",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeEmptyBaseWithOverrides::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> EmptyBase;
	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("pt-BR"), {TEXT("pt")});

	auto Merged = FFallbackMap::Merge(EmptyBase, Overrides);

	TestEqual(TEXT("Empty base with overrides has 1 entry"), Merged.Num(), 1);
	const TArray<FString> Expected = {TEXT("pt")};
	TestEqual(TEXT("Override applied to empty base"), *Merged.Find(TEXT("pt-BR")), Expected);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeEmptyBaseAndEmptyOverrides,
	"LocaleChain.FallbackMap.Merge.EmptyBaseAndEmptyOverrides",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeEmptyBaseAndEmptyOverrides::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> EmptyBase;
	TMap<FString, TArray<FString>> EmptyOverrides;

	auto Merged = FFallbackMap::Merge(EmptyBase, EmptyOverrides);

	TestEqual(TEXT("Empty base + empty overrides = empty result"), Merged.Num(), 0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeDoesNotMutateBase,
	"LocaleChain.FallbackMap.Merge.DoesNotMutateBase",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeDoesNotMutateBase::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> Base;
	Base.Add(TEXT("pt-BR"), {TEXT("pt-PT"), TEXT("pt")});

	const TArray<FString> OriginalChain = {TEXT("pt-PT"), TEXT("pt")};

	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("pt-BR"), {TEXT("pt")});

	// Perform merge (should not modify Base)
	auto Merged = FFallbackMap::Merge(Base, Overrides);

	TestEqual(TEXT("Base dictionary not mutated by merge"),
		*Base.Find(TEXT("pt-BR")), OriginalChain);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FMergeOverrideWithEmptyArray,
	"LocaleChain.FallbackMap.Merge.OverrideWithEmptyArray",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMergeOverrideWithEmptyArray::RunTest(const FString& Parameters)
{
	TMap<FString, TArray<FString>> Base;
	Base.Add(TEXT("pt-BR"), {TEXT("pt-PT"), TEXT("pt")});

	TMap<FString, TArray<FString>> Overrides;
	Overrides.Add(TEXT("pt-BR"), TArray<FString>());

	auto Merged = FFallbackMap::Merge(Base, Overrides);

	TestEqual(TEXT("Override with empty array replaces chain"),
		Merged.Find(TEXT("pt-BR"))->Num(), 0);

	return true;
}
