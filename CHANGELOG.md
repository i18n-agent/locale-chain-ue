# Changelog

## [1.0.0] - 2026-03-14

### Added
- `ULocaleChain::Configure()` initializes the active chain map with 75 default fallback chains covering Chinese, Portuguese, Spanish, French, German, Italian, Dutch, English, Arabic, Norwegian, and Malay regional variants
- `ULocaleChain::ConfigureWithOverrides()` merges Blueprint-friendly overrides (comma-separated values) on top of default fallback chains
- `ULocaleChain::ConfigureCustom()` initializes with a fully custom fallback map, with optional default merging (C++ only)
- `ULocaleChain::Resolve()` walks the fallback chain for the current culture, resolving strings via `FTextLocalizationManager`
- `ULocaleChain::GetChain()` returns the configured fallback chain for a given locale
- `ULocaleChain::IsConfigured()` checks whether chains have been loaded
- `ULocaleChain::Reset()` clears all chains and returns to unconfigured state
- `FFallbackMap::GetDefaults()` provides the full 75-entry default fallback map
- `FFallbackMap::Merge()` utility for combining two fallback maps
- All public functions exposed as `BlueprintCallable` under the "LocaleChain" category
- Thread-safe design using `FRWLock`
- Zero external dependencies (uses only UE core modules: Core, CoreUObject, Engine)
- UE Automation test suite with 40+ tests covering API, FallbackMap integrity, and merge operations
