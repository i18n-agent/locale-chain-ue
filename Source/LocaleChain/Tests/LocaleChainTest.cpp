// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

#include "Misc/AutomationTest.h"
#include "LocaleChain.h"
#include "FallbackMap.h"

// =====================================================================
// Initial State
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNotConfiguredInitially,
	"LocaleChain.API.InitialState.NotConfigured",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNotConfiguredInitially::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	TestFalse(TEXT("Not configured before Configure() is called"),
		ULocaleChain::IsConfigured());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGetChainEmptyInitially,
	"LocaleChain.API.InitialState.GetChainEmpty",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGetChainEmptyInitially::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	TArray<FString> Chain = ULocaleChain::GetChain(TEXT("pt-BR"));
	TestEqual(TEXT("GetChain returns empty before Configure()"), Chain.Num(), 0);
	return true;
}

// =====================================================================
// Configure: Zero-Config Mode
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FZeroConfigSetsConfigured,
	"LocaleChain.API.Configure.ZeroConfig.SetsConfigured",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FZeroConfigSetsConfigured::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();
	TestTrue(TEXT("IsConfigured() returns true after zero-config Configure()"),
		ULocaleChain::IsConfigured());
	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FZeroConfigLoadsDefaults,
	"LocaleChain.API.Configure.ZeroConfig.LoadsDefaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FZeroConfigLoadsDefaults::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	// Spot-check representative chains from multiple language families.
	TestTrue(TEXT("Zero-config has pt-BR"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num() > 0);
	TestTrue(TEXT("Zero-config has en-GB"),
		ULocaleChain::GetChain(TEXT("en-GB")).Num() > 0);
	TestTrue(TEXT("Zero-config has ar-SA"),
		ULocaleChain::GetChain(TEXT("ar-SA")).Num() > 0);
	TestTrue(TEXT("Zero-config has zh-Hant-HK"),
		ULocaleChain::GetChain(TEXT("zh-Hant-HK")).Num() > 0);
	TestTrue(TEXT("Zero-config has nb"),
		ULocaleChain::GetChain(TEXT("nb")).Num() > 0);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FZeroConfigChainValuesMatchDefaults,
	"LocaleChain.API.Configure.ZeroConfig.ChainValuesMatchDefaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FZeroConfigChainValuesMatchDefaults::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	const auto& Defaults = FFallbackMap::GetDefaults();

	// Verify chain values match the defaults map for selected entries.
	const TArray<FString> ExpectedPtBr = {TEXT("pt-PT"), TEXT("pt")};
	TestEqual(TEXT("pt-BR chain matches defaults"),
		ULocaleChain::GetChain(TEXT("pt-BR")), ExpectedPtBr);

	const TArray<FString> ExpectedEnNz = {TEXT("en-AU"), TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-NZ chain matches defaults"),
		ULocaleChain::GetChain(TEXT("en-NZ")), ExpectedEnNz);

	const TArray<FString> ExpectedNn = {TEXT("nb"), TEXT("no")};
	TestEqual(TEXT("nn chain matches defaults"),
		ULocaleChain::GetChain(TEXT("nn")), ExpectedNn);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FConfigureIsIdempotent,
	"LocaleChain.API.Configure.ZeroConfig.Idempotent",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FConfigureIsIdempotent::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	ULocaleChain::Configure();
	TestTrue(TEXT("Configured after first call"), ULocaleChain::IsConfigured());

	ULocaleChain::Configure();
	TestTrue(TEXT("Still configured after second call"), ULocaleChain::IsConfigured());

	// Chains should still be valid after re-configuring.
	const TArray<FString> ExpectedPtBr = {TEXT("pt-PT"), TEXT("pt")};
	TestEqual(TEXT("pt-BR chain correct after double Configure()"),
		ULocaleChain::GetChain(TEXT("pt-BR")), ExpectedPtBr);

	ULocaleChain::Reset();
	return true;
}

// =====================================================================
// Configure: Override Mode (ConfigureWithOverrides)
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FOverrideModeReplacesChain,
	"LocaleChain.API.Configure.OverrideMode.ReplacesChain",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FOverrideModeReplacesChain::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, FString> Overrides;
	Overrides.Add(TEXT("pt-BR"), TEXT("pt"));
	ULocaleChain::ConfigureWithOverrides(Overrides);

	TestTrue(TEXT("Configured after override mode"), ULocaleChain::IsConfigured());

	const TArray<FString> Expected = {TEXT("pt")};
	TestEqual(TEXT("Override mode: pt-BR chain replaced"),
		ULocaleChain::GetChain(TEXT("pt-BR")), Expected);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FOverrideModePreservesOtherDefaults,
	"LocaleChain.API.Configure.OverrideMode.PreservesDefaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FOverrideModePreservesOtherDefaults::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, FString> Overrides;
	Overrides.Add(TEXT("pt-BR"), TEXT("pt"));
	ULocaleChain::ConfigureWithOverrides(Overrides);

	// Unaffected chains should remain from defaults.
	const TArray<FString> ExpectedEnGb = {TEXT("en")};
	TestEqual(TEXT("Override mode: en-GB preserved"),
		ULocaleChain::GetChain(TEXT("en-GB")), ExpectedEnGb);

	const TArray<FString> ExpectedArSa = {TEXT("ar")};
	TestEqual(TEXT("Override mode: ar-SA preserved"),
		ULocaleChain::GetChain(TEXT("ar-SA")), ExpectedArSa);

	const TArray<FString> ExpectedNb = {TEXT("no")};
	TestEqual(TEXT("Override mode: nb preserved"),
		ULocaleChain::GetChain(TEXT("nb")), ExpectedNb);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FOverrideModeAddsNewLocale,
	"LocaleChain.API.Configure.OverrideMode.AddsNewLocale",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FOverrideModeAddsNewLocale::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, FString> Overrides;
	Overrides.Add(TEXT("ja-JP"), TEXT("ja"));
	ULocaleChain::ConfigureWithOverrides(Overrides);

	const TArray<FString> Expected = {TEXT("ja")};
	TestEqual(TEXT("Override mode: ja-JP added"),
		ULocaleChain::GetChain(TEXT("ja-JP")), Expected);

	// Existing defaults should still be present.
	TestTrue(TEXT("Override mode: pt-BR still present from defaults"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num() > 0);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FOverrideModeParsesCommaSeparated,
	"LocaleChain.API.Configure.OverrideMode.ParsesCommaSeparated",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FOverrideModeParsesCommaSeparated::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, FString> Overrides;
	Overrides.Add(TEXT("en-NZ"), TEXT("en-AU, en-GB, en"));
	ULocaleChain::ConfigureWithOverrides(Overrides);

	// Verify whitespace trimming and comma parsing.
	const TArray<FString> Expected = {TEXT("en-AU"), TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("Override mode: comma-separated values parsed correctly"),
		ULocaleChain::GetChain(TEXT("en-NZ")), Expected);

	ULocaleChain::Reset();
	return true;
}

// =====================================================================
// Configure: Full Custom Mode (ConfigureCustom)
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FFullCustomNoMerge,
	"LocaleChain.API.Configure.FullCustom.NoMerge",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFullCustomNoMerge::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, TArray<FString>> Custom;
	Custom.Add(TEXT("custom-A"), {TEXT("custom-B")});
	Custom.Add(TEXT("custom-C"), {TEXT("custom-D")});

	ULocaleChain::ConfigureCustom(Custom, false);

	TestTrue(TEXT("Full custom (no merge): configured"), ULocaleChain::IsConfigured());

	// Only custom entries should exist.
	const TArray<FString> ExpectedA = {TEXT("custom-B")};
	TestEqual(TEXT("Full custom (no merge): has custom-A"),
		ULocaleChain::GetChain(TEXT("custom-A")), ExpectedA);

	const TArray<FString> ExpectedC = {TEXT("custom-D")};
	TestEqual(TEXT("Full custom (no merge): has custom-C"),
		ULocaleChain::GetChain(TEXT("custom-C")), ExpectedC);

	// No defaults should be loaded.
	TestEqual(TEXT("Full custom (no merge): pt-BR not present"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num(), 0);
	TestEqual(TEXT("Full custom (no merge): en-GB not present"),
		ULocaleChain::GetChain(TEXT("en-GB")).Num(), 0);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FFullCustomWithMerge,
	"LocaleChain.API.Configure.FullCustom.WithMerge",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFullCustomWithMerge::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, TArray<FString>> Custom;
	Custom.Add(TEXT("ja-JP"), {TEXT("ja")});

	ULocaleChain::ConfigureCustom(Custom, true);

	// Custom entry should be present.
	const TArray<FString> ExpectedJa = {TEXT("ja")};
	TestEqual(TEXT("Full custom (merge): ja-JP present"),
		ULocaleChain::GetChain(TEXT("ja-JP")), ExpectedJa);

	// Defaults should also be present.
	TestTrue(TEXT("Full custom (merge): pt-BR from defaults"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num() > 0);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FFullCustomWithMergeOverridesExisting,
	"LocaleChain.API.Configure.FullCustom.WithMergeOverridesExisting",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFullCustomWithMergeOverridesExisting::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, TArray<FString>> Custom;
	Custom.Add(TEXT("pt-BR"), {TEXT("pt")});

	ULocaleChain::ConfigureCustom(Custom, true);

	// Custom override should take priority.
	const TArray<FString> ExpectedPtBr = {TEXT("pt")};
	TestEqual(TEXT("Full custom (merge): pt-BR overridden"),
		ULocaleChain::GetChain(TEXT("pt-BR")), ExpectedPtBr);

	// Other defaults still present.
	const TArray<FString> ExpectedEnGb = {TEXT("en")};
	TestEqual(TEXT("Full custom (merge): en-GB from defaults"),
		ULocaleChain::GetChain(TEXT("en-GB")), ExpectedEnGb);

	ULocaleChain::Reset();
	return true;
}

// =====================================================================
// Reset
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FResetClearsConfiguredFlag,
	"LocaleChain.API.Reset.ClearsConfiguredFlag",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FResetClearsConfiguredFlag::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();
	TestTrue(TEXT("Configured before reset"), ULocaleChain::IsConfigured());

	ULocaleChain::Reset();
	TestFalse(TEXT("Not configured after Reset()"), ULocaleChain::IsConfigured());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FResetClearsActiveChains,
	"LocaleChain.API.Reset.ClearsActiveChains",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FResetClearsActiveChains::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();
	TestTrue(TEXT("Chains active before reset"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num() > 0);

	ULocaleChain::Reset();
	TestEqual(TEXT("GetChain returns empty after Reset()"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num(), 0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FResetIsNoopWhenNotConfigured,
	"LocaleChain.API.Reset.NoopWhenNotConfigured",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FResetIsNoopWhenNotConfigured::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	// Should not error when calling Reset without Configure.
	ULocaleChain::Reset();

	TestFalse(TEXT("Reset() is safe when not configured"), ULocaleChain::IsConfigured());
	TestEqual(TEXT("Chains still empty after noop reset"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num(), 0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FResetThenResolveReturnsEmpty,
	"LocaleChain.API.Reset.ResolveReturnsEmpty",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FResetThenResolveReturnsEmpty::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	// Verify we are configured.
	TestTrue(TEXT("Configured before reset"), ULocaleChain::IsConfigured());

	ULocaleChain::Reset();

	// After reset, Resolve should return empty since chains are cleared.
	FString Result = ULocaleChain::Resolve(TEXT("some.key"), TEXT(""));
	TestEqual(TEXT("Resolve returns empty string after Reset()"), Result, FString());

	return true;
}

// =====================================================================
// GetChain Introspection
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGetChainReturnsCorrectChain,
	"LocaleChain.API.GetChain.ReturnsCorrectChain",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGetChainReturnsCorrectChain::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	const TArray<FString> Expected = {TEXT("pt-PT"), TEXT("pt")};
	TestEqual(TEXT("GetChain returns correct chain for pt-BR"),
		ULocaleChain::GetChain(TEXT("pt-BR")), Expected);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGetChainUnknownLocaleReturnsEmpty,
	"LocaleChain.API.GetChain.UnknownLocaleReturnsEmpty",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGetChainUnknownLocaleReturnsEmpty::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	TArray<FString> Chain = ULocaleChain::GetChain(TEXT("xx-UNKNOWN"));
	TestEqual(TEXT("GetChain returns empty for unknown locale"), Chain.Num(), 0);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGetChainMultiLevelChain,
	"LocaleChain.API.GetChain.MultiLevelChain",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGetChainMultiLevelChain::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	// en-NZ has a 3-level chain: en-AU -> en-GB -> en
	const TArray<FString> Expected = {TEXT("en-AU"), TEXT("en-GB"), TEXT("en")};
	TestEqual(TEXT("en-NZ has 3-level fallback chain"),
		ULocaleChain::GetChain(TEXT("en-NZ")), Expected);

	// zh-Hant-MO has a 3-level chain: zh-Hant-HK -> zh-Hant-TW -> zh-Hant
	const TArray<FString> ExpectedMo = {TEXT("zh-Hant-HK"), TEXT("zh-Hant-TW"), TEXT("zh-Hant")};
	TestEqual(TEXT("zh-Hant-MO has 3-level fallback chain"),
		ULocaleChain::GetChain(TEXT("zh-Hant-MO")), ExpectedMo);

	ULocaleChain::Reset();
	return true;
}

// =====================================================================
// Reconfigure (replacing previous configuration)
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FReconfigureReplacesPreviousConfig,
	"LocaleChain.API.Reconfigure.ReplacesPreviousConfig",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FReconfigureReplacesPreviousConfig::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	// First: configure with defaults.
	ULocaleChain::Configure();
	TestTrue(TEXT("First configure loaded chains"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num() > 0);

	// Second: reconfigure with only custom chains (no merge).
	TMap<FString, TArray<FString>> Custom;
	Custom.Add(TEXT("test-locale"), {TEXT("test-fallback")});
	ULocaleChain::ConfigureCustom(Custom, false);

	const TArray<FString> Expected = {TEXT("test-fallback")};
	TestEqual(TEXT("Reconfigure has new custom entry"),
		ULocaleChain::GetChain(TEXT("test-locale")), Expected);

	// Previous defaults should be gone.
	TestEqual(TEXT("Reconfigure removed previous defaults"),
		ULocaleChain::GetChain(TEXT("pt-BR")).Num(), 0);

	ULocaleChain::Reset();
	return true;
}

// =====================================================================
// Resolve (string resolution through the chain)
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FResolveReturnsEmptyWhenNotConfigured,
	"LocaleChain.API.Resolve.ReturnsEmptyWhenNotConfigured",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FResolveReturnsEmptyWhenNotConfigured::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	FString Result = ULocaleChain::Resolve(TEXT("greeting"), TEXT(""));
	TestEqual(TEXT("Resolve returns empty when not configured"), Result, FString());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FResolveReturnsEmptyForMissingKey,
	"LocaleChain.API.Resolve.ReturnsEmptyForMissingKey",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FResolveReturnsEmptyForMissingKey::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	// A key that does not exist in any string table should return empty.
	FString Result = ULocaleChain::Resolve(
		TEXT("nonexistent.key.that.does.not.exist.anywhere"),
		TEXT("NonexistentNamespace"));
	TestEqual(TEXT("Resolve returns empty for missing key"), Result, FString());

	ULocaleChain::Reset();
	return true;
}

// =====================================================================
// Edge Cases
// =====================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FConfigureWithEmptyChainArray,
	"LocaleChain.API.EdgeCases.ConfigureWithEmptyChainArray",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FConfigureWithEmptyChainArray::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();

	TMap<FString, TArray<FString>> Custom;
	Custom.Add(TEXT("empty-chain"), TArray<FString>());

	ULocaleChain::ConfigureCustom(Custom, false);

	TestTrue(TEXT("Configured with empty chain array"), ULocaleChain::IsConfigured());

	// GetChain should return an empty array (the locale has a chain entry
	// but it is empty).
	TArray<FString> Chain = ULocaleChain::GetChain(TEXT("empty-chain"));
	TestEqual(TEXT("Empty chain locale has empty fallback array"), Chain.Num(), 0);

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FIsConfiguredReturnsFalseAfterReset,
	"LocaleChain.API.EdgeCases.IsConfiguredFalseAfterReset",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FIsConfiguredReturnsFalseAfterReset::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	TestFalse(TEXT("IsConfigured false initially"), ULocaleChain::IsConfigured());

	ULocaleChain::Configure();
	TestTrue(TEXT("IsConfigured true after Configure"), ULocaleChain::IsConfigured());

	ULocaleChain::Reset();
	TestFalse(TEXT("IsConfigured false after Reset"), ULocaleChain::IsConfigured());

	ULocaleChain::Configure();
	TestTrue(TEXT("IsConfigured true after re-Configure"), ULocaleChain::IsConfigured());

	ULocaleChain::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FGetChainReturnsEmptyForNonexistentLocale,
	"LocaleChain.API.EdgeCases.GetChainEmptyForNonexistentLocale",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGetChainReturnsEmptyForNonexistentLocale::RunTest(const FString& Parameters)
{
	ULocaleChain::Reset();
	ULocaleChain::Configure();

	// A locale not in the map should return an empty array.
	TArray<FString> Chain = ULocaleChain::GetChain(TEXT("xx-UNKNOWN"));
	TestEqual(TEXT("xx-UNKNOWN not in active chains"), Chain.Num(), 0);

	ULocaleChain::Reset();
	return true;
}
