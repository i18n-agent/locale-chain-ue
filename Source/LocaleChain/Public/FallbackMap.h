// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"

/**
 * Static fallback chain data for locale resolution.
 *
 * Contains the canonical 75-entry fallback map covering Chinese, Portuguese,
 * Spanish, French, German, Italian, Dutch, English, Arabic, Norwegian, and Malay
 * locale families. Use Merge() to combine custom overrides with the defaults.
 */
class LOCALECHAIN_API FFallbackMap
{
public:
	/** Returns the full default fallback chain map (75 entries). */
	static const TMap<FString, TArray<FString>>& GetDefaults();

	/**
	 * Merges custom overrides into a copy of the base map.
	 *
	 * For each key in Overrides, the entry replaces any existing entry in Base.
	 * Keys in Base that are not present in Overrides are preserved unchanged.
	 *
	 * @param Base       The base fallback map (typically GetDefaults()).
	 * @param Overrides  Custom entries that take priority over Base.
	 * @return           A new map with overrides applied on top of the base.
	 */
	static TMap<FString, TArray<FString>> Merge(
		const TMap<FString, TArray<FString>>& Base,
		const TMap<FString, TArray<FString>>& Overrides);

private:
	FFallbackMap() = delete;

	static TMap<FString, TArray<FString>> BuildDefaults();
};
