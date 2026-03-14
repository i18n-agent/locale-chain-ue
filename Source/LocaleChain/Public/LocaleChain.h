// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LocaleChain.generated.h"

/**
 * Blueprint-callable locale chain resolver for Unreal Engine 5.3+.
 *
 * Provides configurable locale fallback chains so that when a localized string
 * is missing for a specific regional locale, the system walks the chain to find
 * the best available translation before falling back to the default language.
 *
 * Usage from C++:
 *   ULocaleChain::Configure();                           // zero-config defaults
 *   FString Msg = ULocaleChain::Resolve(Key, Namespace); // walk chain
 *
 * Usage from Blueprints:
 *   Call "Configure" once at startup, then "Resolve" per string.
 */
UCLASS()
class LOCALECHAIN_API ULocaleChain : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// -----------------------------------------------------------------------
	// Configuration
	// -----------------------------------------------------------------------

	/**
	 * Zero-config: loads the full default fallback chains (75 entries).
	 * Thread-safe. Replaces any previous configuration.
	 */
	UFUNCTION(BlueprintCallable, Category = "LocaleChain")
	static void Configure();

	/**
	 * Loads defaults then merges in the provided overrides.
	 * Overrides replace matching keys; unmatched defaults are preserved.
	 *
	 * @param Overrides  Custom fallback chains that take priority.
	 */
	UFUNCTION(BlueprintCallable, Category = "LocaleChain")
	static void ConfigureWithOverrides(const TMap<FString, FString>& Overrides);

	/**
	 * Full control: supply a complete chain map and optionally merge with defaults.
	 *
	 * @param CustomChains    The custom fallback chains to use.
	 * @param bMergeDefaults  If true, custom chains are merged on top of defaults.
	 *                        If false, only CustomChains are used.
	 */
	static void ConfigureCustom(
		const TMap<FString, TArray<FString>>& CustomChains,
		bool bMergeDefaults = true);

	/**
	 * Clears all configured chains and resets to an unconfigured state.
	 * Thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "LocaleChain")
	static void Reset();

	// -----------------------------------------------------------------------
	// Resolution
	// -----------------------------------------------------------------------

	/**
	 * Resolves a localized string by walking the fallback chain for the
	 * current culture. Tries the current locale first, then each fallback
	 * in order, returning the first non-empty result.
	 *
	 * @param Key        The localization key to look up.
	 * @param Namespace  The localization namespace (defaults to empty).
	 * @return           The resolved localized string, or empty if not found.
	 */
	UFUNCTION(BlueprintCallable, Category = "LocaleChain")
	static FString Resolve(const FString& Key, const FString& Namespace = TEXT(""));

	// -----------------------------------------------------------------------
	// Introspection (useful for debugging and tooling)
	// -----------------------------------------------------------------------

	/**
	 * Returns the fallback chain for a given locale, or an empty array
	 * if no chain is configured for that locale.
	 *
	 * @param Locale  The locale tag to query (e.g. "zh-Hant-HK").
	 * @return        Ordered array of fallback locale tags.
	 */
	UFUNCTION(BlueprintCallable, Category = "LocaleChain")
	static TArray<FString> GetChain(const FString& Locale);

	/**
	 * Returns true if Configure() has been called and chains are loaded.
	 */
	UFUNCTION(BlueprintCallable, Category = "LocaleChain")
	static bool IsConfigured();

private:
	/** The active fallback chain map. Guarded by ChainLock. */
	static TMap<FString, TArray<FString>> ActiveChains;

	/** Whether Configure() has been called. */
	static bool bConfigured;

	/** Read-write lock protecting ActiveChains and bConfigured. */
	static FRWLock ChainLock;

	/**
	 * Attempts to find a display string for the given key/namespace in
	 * the specified locale using UE's localization manager.
	 *
	 * @return true if a non-empty localized string was found.
	 */
	static bool TryGetLocalizedString(
		const FString& Locale,
		const FString& Namespace,
		const FString& Key,
		FString& OutResult);

	/**
	 * Converts a Blueprint-friendly TMap<FString, FString> (comma-separated
	 * values) into the internal TMap<FString, TArray<FString>> format.
	 */
	static TMap<FString, TArray<FString>> ParseOverrides(
		const TMap<FString, FString>& Overrides);
};
