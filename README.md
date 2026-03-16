# locale-chain-ue

Smart locale fallback chains for Unreal Engine 5.3+ -- because pt-BR users deserve pt-PT, not English.

## The Problem

Unreal Engine's built-in localization system supports culture remapping, but it only falls back along the standard IETF subtag hierarchy (e.g., `pt-BR` -> `pt` -> default). It does not support lateral fallbacks between regional variants. If a `pt-BR` user is missing a translation, they get the default language instead of a perfectly good `pt-PT` translation.

**Example:** Your game has `pt-PT` and `pt` localization targets. A `pt-BR` user loads the game. UE tries `pt-BR`, fails, skips `pt-PT` entirely, and falls back to `pt` or English. The user sees untranslated strings when a sibling locale had the answer.

The same problem affects `es-MX` -> `es-419` -> `es`, `fr-CA` -> `fr`, `zh-Hant-HK` -> `zh-Hant-TW` -> `zh-Hant`, and every other regional variant family.

## The Solution

One function call. Drop the plugin into your project and call `ULocaleChain::Configure()` at startup.

`locale-chain-ue` resolves localized strings by walking a configurable fallback chain through UE's `FTextLocalizationManager`. Every key is resolved from the most specific locale that defines it, falling through siblings and parent locales until a value is found.

## Installation

Clone or download the plugin into your project's `Plugins/` directory:

```
YourProject/
  Plugins/
    LocaleChain/
      LocaleChain.uplugin
      Source/
        LocaleChain/
          ...
```

Then regenerate your project files:

- **Windows:** Right-click your `.uproject` file and select "Generate Visual Studio project files"
- **Mac:** Right-click your `.uproject` file and select "Generate Xcode project"
- **Command line:** `UnrealBuildTool -projectfiles -project="YourProject.uproject" -game -engine`

Requires Unreal Engine 5.3+.

## Quick Start

### C++

```cpp
#include "LocaleChain.h"

// In your GameInstance or module startup:
void UMyGameInstance::Init()
{
    Super::Init();

    // 1. Configure fallback chains (call once at startup)
    ULocaleChain::Configure();
}

// Anywhere in your game code:
void UMyWidget::UpdateUI()
{
    // 2. Resolve with per-key fallback through the chain
    FString Greeting = ULocaleChain::Resolve(TEXT("greeting"), TEXT("MyNamespace"));
    GreetingText->SetText(FText::FromString(Greeting));
}
```

### Blueprint

1. Call **Configure** once at startup (e.g., in your GameInstance's `Init` event):

   ![Blueprint: Call Configure node](https://img.shields.io/badge/Blueprint-Configure-blue)

   `LocaleChain > Configure`

2. Call **Resolve** wherever you need a localized string:

   ![Blueprint: Call Resolve node](https://img.shields.io/badge/Blueprint-Resolve-green)

   `LocaleChain > Resolve` with inputs:
   - **Key**: `"greeting"`
   - **Namespace**: `"MyNamespace"` (optional, defaults to empty)
   - **Return Value**: The resolved localized string

3. Use **Get Chain** to inspect fallback chains for debugging:

   `LocaleChain > GetChain` with input **Locale**: `"pt-BR"`
   - Returns: `["pt-PT", "pt"]`

## API Reference

### Configure

```cpp
// Use all 75 built-in fallback chains
ULocaleChain::Configure();
```

Zero-config: loads the full default fallback map (75 entries covering 11 language families). Thread-safe. Replaces any previous configuration.

### ConfigureWithOverrides

```cpp
// Override specific chains while keeping all defaults
TMap<FString, FString> Overrides;
Overrides.Add(TEXT("pt-BR"), TEXT("pt"));           // Simplify pt-BR chain
Overrides.Add(TEXT("sv-FI"), TEXT("sv"));            // Add new chain
Overrides.Add(TEXT("en-NZ"), TEXT("en-AU, en-GB, en")); // Comma-separated values
ULocaleChain::ConfigureWithOverrides(Overrides);
```

Blueprint-friendly: values are comma-separated strings. Your overrides replace matching keys in the default map. All other defaults remain.

### ConfigureCustom (C++ only)

```cpp
// Full control -- only use your chains
TMap<FString, TArray<FString>> Custom;
Custom.Add(TEXT("pt-BR"), {TEXT("pt-PT"), TEXT("pt")});
Custom.Add(TEXT("es-MX"), {TEXT("es-419"), TEXT("es")});
ULocaleChain::ConfigureCustom(Custom, false); // false = don't merge with defaults

// Or merge custom chains on top of defaults
TMap<FString, TArray<FString>> Extra;
Extra.Add(TEXT("sv-FI"), {TEXT("sv")});
ULocaleChain::ConfigureCustom(Extra, true); // true = merge with defaults
```

### Resolve

```cpp
// Resolve a localized string with per-key fallback
FString Result = ULocaleChain::Resolve(TEXT("greeting"), TEXT("MyNamespace"));
```

Walks the fallback chain for the current culture. Tries the current locale first, then each fallback in order, returning the first non-empty result from `FTextLocalizationManager`. Returns an empty string if no translation is found.

### GetChain

```cpp
// Inspect the fallback chain for a locale
TArray<FString> Chain = ULocaleChain::GetChain(TEXT("pt-BR"));
// Returns: ["pt-PT", "pt"]
```

Returns the configured fallback chain (not including the locale itself). Returns an empty array if the locale has no chain or the resolver is not configured.

### IsConfigured

```cpp
// Check whether chains have been loaded
bool bReady = ULocaleChain::IsConfigured();
```

### Reset

```cpp
// Clear all chains and return to unconfigured state
ULocaleChain::Reset();
```

Thread-safe. After reset, `Resolve` still works but without fallback chains (only the current locale is tried).

## Concurrency Safety

All public functions are thread-safe. The active chain map is protected by an `FRWLock`. Call `Configure` once at startup and use `Resolve`/`GetChain` freely from any thread, including game thread, render thread, and async tasks.

## Default Fallback Map

75 built-in chains covering 11 language families.

### Chinese

| Locale | Fallback Chain |
|--------|---------------|
| zh-Hant-HK | zh-Hant-TW -> zh-Hant -> (default) |
| zh-Hant-MO | zh-Hant-HK -> zh-Hant-TW -> zh-Hant -> (default) |
| zh-Hant-TW | zh-Hant -> (default) |
| zh-Hans-SG | zh-Hans -> (default) |
| zh-Hans-MY | zh-Hans -> (default) |

### Portuguese

| Locale | Fallback Chain |
|--------|---------------|
| pt-BR | pt-PT -> pt -> (default) |
| pt-PT | pt -> (default) |
| pt-AO | pt-PT -> pt -> (default) |
| pt-MZ | pt-PT -> pt -> (default) |

### Spanish

| Locale | Fallback Chain |
|--------|---------------|
| es-419 | es -> (default) |
| es-MX | es-419 -> es -> (default) |
| es-AR | es-419 -> es -> (default) |
| es-CO | es-419 -> es -> (default) |
| es-CL | es-419 -> es -> (default) |
| es-PE | es-419 -> es -> (default) |
| es-VE | es-419 -> es -> (default) |
| es-EC | es-419 -> es -> (default) |
| es-GT | es-419 -> es -> (default) |
| es-CU | es-419 -> es -> (default) |
| es-BO | es-419 -> es -> (default) |
| es-DO | es-419 -> es -> (default) |
| es-HN | es-419 -> es -> (default) |
| es-PY | es-419 -> es -> (default) |
| es-SV | es-419 -> es -> (default) |
| es-NI | es-419 -> es -> (default) |
| es-CR | es-419 -> es -> (default) |
| es-PA | es-419 -> es -> (default) |
| es-UY | es-419 -> es -> (default) |
| es-PR | es-419 -> es -> (default) |

### French

| Locale | Fallback Chain |
|--------|---------------|
| fr-CA | fr -> (default) |
| fr-BE | fr -> (default) |
| fr-CH | fr -> (default) |
| fr-LU | fr -> (default) |
| fr-MC | fr -> (default) |
| fr-SN | fr -> (default) |
| fr-CI | fr -> (default) |
| fr-ML | fr -> (default) |
| fr-CM | fr -> (default) |
| fr-MG | fr -> (default) |
| fr-CD | fr -> (default) |

### German

| Locale | Fallback Chain |
|--------|---------------|
| de-AT | de -> (default) |
| de-CH | de -> (default) |
| de-LU | de -> (default) |
| de-LI | de -> (default) |

### Italian

| Locale | Fallback Chain |
|--------|---------------|
| it-CH | it -> (default) |

### Dutch

| Locale | Fallback Chain |
|--------|---------------|
| nl-BE | nl -> (default) |

### English

| Locale | Fallback Chain |
|--------|---------------|
| en-GB | en -> (default) |
| en-AU | en-GB -> en -> (default) |
| en-NZ | en-AU -> en-GB -> en -> (default) |
| en-IN | en-GB -> en -> (default) |
| en-CA | en -> (default) |
| en-ZA | en-GB -> en -> (default) |
| en-IE | en-GB -> en -> (default) |
| en-SG | en-GB -> en -> (default) |

### Arabic

| Locale | Fallback Chain |
|--------|---------------|
| ar-SA | ar -> (default) |
| ar-EG | ar -> (default) |
| ar-AE | ar -> (default) |
| ar-MA | ar -> (default) |
| ar-DZ | ar -> (default) |
| ar-IQ | ar -> (default) |
| ar-KW | ar -> (default) |
| ar-QA | ar -> (default) |
| ar-BH | ar -> (default) |
| ar-OM | ar -> (default) |
| ar-JO | ar -> (default) |
| ar-LB | ar -> (default) |
| ar-TN | ar -> (default) |
| ar-LY | ar -> (default) |
| ar-SD | ar -> (default) |
| ar-YE | ar -> (default) |

### Norwegian

| Locale | Fallback Chain |
|--------|---------------|
| nb | no -> (default) |
| nn | nb -> no -> (default) |

### Malay

| Locale | Fallback Chain |
|--------|---------------|
| ms-MY | ms -> (default) |
| ms-SG | ms -> (default) |
| ms-BN | ms -> (default) |

## How It Works

1. `Configure()` initializes the active chain map with the default fallback data (or your custom overrides).
2. When `Resolve()` is called, it determines the current culture via `FInternationalization::Get().GetCurrentCulture()`.
3. It first tries to find the string in the current locale via `FTextLocalizationManager::FindDisplayString()`.
4. If not found, it walks the fallback chain for the current locale, trying each fallback locale in order.
5. The first non-empty result is returned. If nothing is found, an empty string is returned.
6. All shared state is protected by `FRWLock` for thread safety.

## Distribution

This plugin is distributed via GitHub Releases with pre-built binaries. See [BUILD.md](BUILD.md) for packaging instructions.

## Requirements

- Unreal Engine 5.3+
- Zero external dependencies (uses only UE core modules)

## FAQ

**Does this replace UE's built-in localization?**
No. `locale-chain-ue` complements UE's localization system by adding configurable lateral fallback chains. You still use the Localization Dashboard, String Tables, and `FText` as normal. This plugin adds fallback resolution on top.

**Performance impact?**
Negligible. The fallback chain is only walked when the current locale is missing a key. Each step is a single `FTextLocalizationManager::FindDisplayString()` call. For games with complete translations in the primary locale, the chain is never walked.

**Can I use this with String Tables?**
Yes. `Resolve` works with any strings loaded into `FTextLocalizationManager`, including String Tables, .locres files, and programmatically added entries.

**Is it thread-safe?**
Yes. All public functions use `FRWLock` for concurrent access. `Configure` should be called once at startup. `Resolve` and `GetChain` can be called from any thread.

**What happens if I call Resolve without Configure?**
It still works -- it tries the current locale only, with no fallback. You get the same behavior as not having this plugin.

**Can I use this from Blueprints?**
Yes. `Configure`, `ConfigureWithOverrides`, `Resolve`, `GetChain`, `IsConfigured`, and `Reset` are all exposed as `BlueprintCallable` functions under the "LocaleChain" category.

**What about the UE Marketplace?**
UE Marketplace submission requires a separate manual review process with Epic Games. This plugin is distributed via GitHub Releases for now. Marketplace submission may follow in a future release.

## Contributing

- Open issues for bugs or feature requests.
- PRs welcome, especially for adding new locale fallback chains.
- See [BUILD.md](BUILD.md) for local build and testing instructions.

## Example

A minimal Unreal Engine 5.3+ example project is included in the [`example/`](./example/) directory. It demonstrates the locale chain resolving keys with fallback from `pt-BR -> pt -> en`. Open the project in Unreal Editor and check the Output Log for resolved translations.

See [`example/README.md`](./example/README.md) for full setup instructions.

## License

MIT License - see [LICENSE](LICENSE) file.

Built by [i18nagent.ai](https://i18nagent.ai)
