// Copyright (c) 2026 i18n-agent. All rights reserved.
// Licensed under the MIT License.

#include "LocaleChain.h"
#include "FallbackMap.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/TextLocalizationManager.h"

// -----------------------------------------------------------------------
// Static member definitions
// -----------------------------------------------------------------------

TMap<FString, TArray<FString>> ULocaleChain::ActiveChains;
bool ULocaleChain::bConfigured = false;
FRWLock ULocaleChain::ChainLock;

// -----------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------

void ULocaleChain::Configure()
{
	FRWScopeLock WriteLock(ChainLock, SLT_Write);
	ActiveChains = FFallbackMap::GetDefaults();
	bConfigured = true;
}

void ULocaleChain::ConfigureWithOverrides(const TMap<FString, FString>& Overrides)
{
	TMap<FString, TArray<FString>> ParsedOverrides = ParseOverrides(Overrides);

	FRWScopeLock WriteLock(ChainLock, SLT_Write);
	ActiveChains = FFallbackMap::Merge(FFallbackMap::GetDefaults(), ParsedOverrides);
	bConfigured = true;
}

void ULocaleChain::ConfigureCustom(
	const TMap<FString, TArray<FString>>& CustomChains,
	bool bMergeDefaults)
{
	FRWScopeLock WriteLock(ChainLock, SLT_Write);

	if (bMergeDefaults)
	{
		ActiveChains = FFallbackMap::Merge(FFallbackMap::GetDefaults(), CustomChains);
	}
	else
	{
		ActiveChains = CustomChains;
	}

	bConfigured = true;
}

void ULocaleChain::Reset()
{
	FRWScopeLock WriteLock(ChainLock, SLT_Write);
	ActiveChains.Empty();
	bConfigured = false;
}

// -----------------------------------------------------------------------
// Resolution
// -----------------------------------------------------------------------

FString ULocaleChain::Resolve(const FString& Key, const FString& Namespace)
{
	// Determine the current culture locale tag.
	const FString CurrentLocale = FInternationalization::Get().GetCurrentCulture()->GetName();

	FString Result;

	// Try the current locale first.
	if (TryGetLocalizedString(CurrentLocale, Namespace, Key, Result))
	{
		return Result;
	}

	// Walk the fallback chain.
	{
		FRWScopeLock ReadLock(ChainLock, SLT_ReadOnly);

		if (bConfigured)
		{
			const TArray<FString>* Chain = ActiveChains.Find(CurrentLocale);
			if (Chain != nullptr)
			{
				for (const FString& FallbackLocale : *Chain)
				{
					if (TryGetLocalizedString(FallbackLocale, Namespace, Key, Result))
					{
						return Result;
					}
				}
			}
		}
	}

	// Nothing found in the chain; return empty string.
	return FString();
}

// -----------------------------------------------------------------------
// Introspection
// -----------------------------------------------------------------------

TArray<FString> ULocaleChain::GetChain(const FString& Locale)
{
	FRWScopeLock ReadLock(ChainLock, SLT_ReadOnly);

	const TArray<FString>* Chain = ActiveChains.Find(Locale);
	if (Chain != nullptr)
	{
		return *Chain;
	}
	return TArray<FString>();
}

bool ULocaleChain::IsConfigured()
{
	FRWScopeLock ReadLock(ChainLock, SLT_ReadOnly);
	return bConfigured;
}

// -----------------------------------------------------------------------
// Private helpers
// -----------------------------------------------------------------------

bool ULocaleChain::TryGetLocalizedString(
	const FString& Locale,
	const FString& Namespace,
	const FString& Key,
	FString& OutResult)
{
	FTextLocalizationManager& LocManager = FTextLocalizationManager::Get();

	// GetDisplayString returns a pointer to the display string for the given
	// namespace/key/culture combination, or nullptr if not found.
	const FString* DisplayString = LocManager.FindDisplayString(Namespace, Key, &Locale);

	if (DisplayString != nullptr && !DisplayString->IsEmpty())
	{
		OutResult = *DisplayString;
		return true;
	}

	return false;
}

TMap<FString, TArray<FString>> ULocaleChain::ParseOverrides(
	const TMap<FString, FString>& Overrides)
{
	TMap<FString, TArray<FString>> Result;
	Result.Reserve(Overrides.Num());

	for (const auto& Pair : Overrides)
	{
		TArray<FString> Chain;
		Pair.Value.ParseIntoArray(Chain, TEXT(","), true);

		// Trim whitespace from each element.
		for (FString& Entry : Chain)
		{
			Entry.TrimStartAndEndInline();
		}

		Result.Add(Pair.Key, MoveTemp(Chain));
	}

	return Result;
}
