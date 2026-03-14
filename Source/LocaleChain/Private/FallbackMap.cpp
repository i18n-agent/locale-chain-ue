// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

#include "FallbackMap.h"

const TMap<FString, TArray<FString>>& FFallbackMap::GetDefaults()
{
	static const TMap<FString, TArray<FString>> Defaults = BuildDefaults();
	return Defaults;
}

TMap<FString, TArray<FString>> FFallbackMap::Merge(
	const TMap<FString, TArray<FString>>& Base,
	const TMap<FString, TArray<FString>>& Overrides)
{
	TMap<FString, TArray<FString>> Result = Base;
	for (const auto& Pair : Overrides)
	{
		Result.Add(Pair.Key, Pair.Value);
	}
	return Result;
}

TMap<FString, TArray<FString>> FFallbackMap::BuildDefaults()
{
	TMap<FString, TArray<FString>> Map;
	Map.Reserve(75);

	// -----------------------------------------------------------------------
	// Chinese (5 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("zh-Hant-HK"), {TEXT("zh-Hant-TW"), TEXT("zh-Hant")});
	Map.Add(TEXT("zh-Hant-MO"), {TEXT("zh-Hant-HK"), TEXT("zh-Hant-TW"), TEXT("zh-Hant")});
	Map.Add(TEXT("zh-Hant-TW"), {TEXT("zh-Hant")});
	Map.Add(TEXT("zh-Hans-SG"), {TEXT("zh-Hans")});
	Map.Add(TEXT("zh-Hans-MY"), {TEXT("zh-Hans")});

	// -----------------------------------------------------------------------
	// Portuguese (4 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("pt-BR"), {TEXT("pt-PT"), TEXT("pt")});
	Map.Add(TEXT("pt-PT"), {TEXT("pt")});
	Map.Add(TEXT("pt-AO"), {TEXT("pt-PT"), TEXT("pt")});
	Map.Add(TEXT("pt-MZ"), {TEXT("pt-PT"), TEXT("pt")});

	// -----------------------------------------------------------------------
	// Spanish (20 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("es-419"), {TEXT("es")});
	Map.Add(TEXT("es-MX"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-AR"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-CO"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-CL"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-PE"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-VE"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-EC"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-GT"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-CU"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-BO"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-DO"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-HN"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-PY"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-SV"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-NI"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-CR"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-PA"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-UY"),  {TEXT("es-419"), TEXT("es")});
	Map.Add(TEXT("es-PR"),  {TEXT("es-419"), TEXT("es")});

	// -----------------------------------------------------------------------
	// French (11 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("fr-CA"), {TEXT("fr")});
	Map.Add(TEXT("fr-BE"), {TEXT("fr")});
	Map.Add(TEXT("fr-CH"), {TEXT("fr")});
	Map.Add(TEXT("fr-LU"), {TEXT("fr")});
	Map.Add(TEXT("fr-MC"), {TEXT("fr")});
	Map.Add(TEXT("fr-SN"), {TEXT("fr")});
	Map.Add(TEXT("fr-CI"), {TEXT("fr")});
	Map.Add(TEXT("fr-ML"), {TEXT("fr")});
	Map.Add(TEXT("fr-CM"), {TEXT("fr")});
	Map.Add(TEXT("fr-MG"), {TEXT("fr")});
	Map.Add(TEXT("fr-CD"), {TEXT("fr")});

	// -----------------------------------------------------------------------
	// German (4 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("de-AT"), {TEXT("de")});
	Map.Add(TEXT("de-CH"), {TEXT("de")});
	Map.Add(TEXT("de-LU"), {TEXT("de")});
	Map.Add(TEXT("de-LI"), {TEXT("de")});

	// -----------------------------------------------------------------------
	// Italian (1 entry)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("it-CH"), {TEXT("it")});

	// -----------------------------------------------------------------------
	// Dutch (1 entry)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("nl-BE"), {TEXT("nl")});

	// -----------------------------------------------------------------------
	// English (8 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("en-GB"), {TEXT("en")});
	Map.Add(TEXT("en-AU"), {TEXT("en-GB"), TEXT("en")});
	Map.Add(TEXT("en-NZ"), {TEXT("en-AU"), TEXT("en-GB"), TEXT("en")});
	Map.Add(TEXT("en-IN"), {TEXT("en-GB"), TEXT("en")});
	Map.Add(TEXT("en-CA"), {TEXT("en")});
	Map.Add(TEXT("en-ZA"), {TEXT("en-GB"), TEXT("en")});
	Map.Add(TEXT("en-IE"), {TEXT("en-GB"), TEXT("en")});
	Map.Add(TEXT("en-SG"), {TEXT("en-GB"), TEXT("en")});

	// -----------------------------------------------------------------------
	// Arabic (16 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("ar-SA"), {TEXT("ar")});
	Map.Add(TEXT("ar-EG"), {TEXT("ar")});
	Map.Add(TEXT("ar-AE"), {TEXT("ar")});
	Map.Add(TEXT("ar-MA"), {TEXT("ar")});
	Map.Add(TEXT("ar-DZ"), {TEXT("ar")});
	Map.Add(TEXT("ar-IQ"), {TEXT("ar")});
	Map.Add(TEXT("ar-KW"), {TEXT("ar")});
	Map.Add(TEXT("ar-QA"), {TEXT("ar")});
	Map.Add(TEXT("ar-BH"), {TEXT("ar")});
	Map.Add(TEXT("ar-OM"), {TEXT("ar")});
	Map.Add(TEXT("ar-JO"), {TEXT("ar")});
	Map.Add(TEXT("ar-LB"), {TEXT("ar")});
	Map.Add(TEXT("ar-TN"), {TEXT("ar")});
	Map.Add(TEXT("ar-LY"), {TEXT("ar")});
	Map.Add(TEXT("ar-SD"), {TEXT("ar")});
	Map.Add(TEXT("ar-YE"), {TEXT("ar")});

	// -----------------------------------------------------------------------
	// Norwegian (2 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("nb"), {TEXT("no")});
	Map.Add(TEXT("nn"), {TEXT("nb"), TEXT("no")});

	// -----------------------------------------------------------------------
	// Malay (3 entries)
	// -----------------------------------------------------------------------
	Map.Add(TEXT("ms-MY"), {TEXT("ms")});
	Map.Add(TEXT("ms-SG"), {TEXT("ms")});
	Map.Add(TEXT("ms-BN"), {TEXT("ms")});

	return Map;
}
