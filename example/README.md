# LocaleChain Example Project

Minimal Unreal Engine 5.4 project demonstrating the LocaleChain plugin.

## What It Does

On module startup (`FExampleModule::StartupModule`), the example:

1. Calls `ULocaleChain::Configure()` to load all 75 default fallback chains
2. Inspects the `pt-BR` fallback chain (`pt-PT -> pt`) via `GetChain()`
3. Resolves 3 localization keys (`greeting`, `farewell`, `welcome`) in the `Game` namespace
4. Logs everything to the output log under `LogLocaleChainExample`

## Project Structure

```
example/
  Example.uproject              -- Project descriptor (references LocaleChain plugin)
  Config/
    DefaultEngine.ini           -- Localization paths + default culture
    DefaultGame.ini             -- Project settings
    DefaultEditor.ini           -- Editor settings
  Source/Example/
    Example.Build.cs            -- Module build rules (depends on LocaleChain)
    Example.Target.cs           -- Game target
    ExampleEditor.Target.cs     -- Editor target
    ExampleModule.h             -- Module header
    ExampleModule.cpp           -- Module implementation (the demo code)
  Plugins/
    LocaleChain/                -- Copy of plugin source (see Setup below)
```

## Setup

The `Plugins/LocaleChain/` directory contains a copy of the plugin source files. If you cloned this repo fresh, the plugin files are already included. To use the latest plugin source from the parent directory instead:

```bash
# From the example/ directory:
rm -rf Plugins/LocaleChain
cp -r ../ Plugins/LocaleChain
rm -rf Plugins/LocaleChain/example  # Remove recursive copy
```

In a standalone project (outside this repo), clone or copy the plugin:

```bash
cd YourProject/Plugins/
git clone https://github.com/i18n-agent/locale-chain-ue.git LocaleChain
```

## How to Build

### From UE Editor

1. Open `Example.uproject` in Unreal Editor 5.4
2. The editor will compile the project and plugin automatically
3. Check **Window > Developer Tools > Output Log** for `LogLocaleChainExample` entries

### From Command Line (Mac)

```bash
"/Users/Shared/Epic Games/UE_5.4/Engine/Build/BatchFiles/RunUAT.sh" \
  BuildCookRun \
  -project="$(pwd)/Example.uproject" \
  -noP4 -platform=Mac -clientconfig=Development -build -cook -stage
```

### From Command Line (Windows)

```cmd
"C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat" ^
  BuildCookRun ^
  -project="%CD%\Example.uproject" ^
  -noP4 -platform=Win64 -clientconfig=Development -build -cook -stage
```

## Expected Log Output

When the module loads, you will see:

```
LogLocaleChainExample: === LocaleChain Example: StartupModule ===
LogLocaleChainExample: ULocaleChain::Configure() called. IsConfigured = true
LogLocaleChainExample: pt-BR fallback chain: pt-PT -> pt
LogLocaleChainExample: Current culture: en
LogLocaleChainExample: Resolve("greeting", "Game") = ""
LogLocaleChainExample: Resolve("farewell", "Game") = ""
LogLocaleChainExample: Resolve("welcome",  "Game") = ""
LogLocaleChainExample: All keys resolved to empty -- this is expected if no localization data (.locres / String Tables) is loaded. The fallback chain is configured and ready.
LogLocaleChainExample: === LocaleChain Example: Done ===
```

The empty resolve results are expected -- the chain configuration works, but no `.locres` files or String Tables are loaded in this minimal example. In a real project, UE's localization pipeline would populate the `FTextLocalizationManager` with data, and `Resolve()` would walk the fallback chain to find the best match.

## Notes

- This project targets UE 5.4 but the plugin is compatible with any UE 5.3+ version. Adjust `EngineAssociation` in `Example.uproject` as needed.
- Command-line builds require an Xcode version compatible with your UE version (UE 5.4 expects Xcode 15.x). If your Xcode is too new, open the project in the UE Editor instead, which handles compilation internally.
