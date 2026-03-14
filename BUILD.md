# Building and Packaging locale-chain-ue

This document covers how to build, test, and package the LocaleChain plugin locally. Since Unreal Engine is not available on standard CI runners (GitHub Actions, etc.), all builds are done locally.

## Prerequisites

- Unreal Engine 5.3, 5.4, or 5.5 installed via the Epic Games Launcher
- Visual Studio 2022 (Windows) or Xcode 15+ (Mac)
- Platform SDKs for your target platforms (Win64, Mac, Linux)

### Engine Installation Paths

| Platform | Default Path |
|----------|-------------|
| Windows | `C:\Program Files\Epic Games\UE_5.X` |
| Mac | `/Users/Shared/Epic Games/UE_5.X` |

## Local Build (Development)

### 1. Set Up a Host Project

Create a minimal UE project to host the plugin during development:

```bash
# Clone the plugin into your project's Plugins directory
cd YourProject/Plugins/
git clone https://github.com/i18n-agent/locale-chain-ue.git LocaleChain
```

### 2. Regenerate Project Files

**Windows:**
```
Right-click YourProject.uproject -> "Generate Visual Studio project files"
```

**Mac:**
```
Right-click YourProject.uproject -> Services -> "Generate Xcode project"
```

**Command line:**
```bash
# Windows
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat" \
  -project="C:\Projects\YourProject\YourProject.uproject" \
  -GenerateProjectFiles

# Mac
/Users/Shared/Epic\ Games/UE_5.3/Engine/Build/BatchFiles/RunUAT.sh \
  -project="/Users/you/Projects/YourProject/YourProject.uproject" \
  -GenerateProjectFiles
```

### 3. Build

Open the generated solution/project and build in Development Editor configuration, or use the command line:

```bash
# Windows
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat" \
  BuildCookRun \
  -project="C:\Projects\YourProject\YourProject.uproject" \
  -noP4 -platform=Win64 -clientconfig=Development -build

# Mac
/Users/Shared/Epic\ Games/UE_5.3/Engine/Build/BatchFiles/RunUAT.sh \
  BuildCookRun \
  -project="/Users/you/Projects/YourProject/YourProject.uproject" \
  -noP4 -platform=Mac -clientconfig=Development -build
```

## Running Tests

The plugin includes a UE Automation test suite. Run tests from the editor or command line:

### From the Editor

1. Open your project in the UE Editor
2. Go to **Tools > Session Frontend > Automation**
3. Filter for `LocaleChain`
4. Select all tests and click **Run**

### From the Command Line

```bash
# Windows
"C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" \
  "C:\Projects\YourProject\YourProject.uproject" \
  -ExecCmds="Automation RunTests LocaleChain; Quit" \
  -unattended -nopause -NullRHI -nosplash -log

# Mac
/Users/Shared/Epic\ Games/UE_5.3/Engine/Binaries/Mac/UnrealEditor-Cmd \
  "/Users/you/Projects/YourProject/YourProject.uproject" \
  -ExecCmds="Automation RunTests LocaleChain; Quit" \
  -unattended -nopause -NullRHI -nosplash -log
```

Tests are located in `Source/LocaleChain/Tests/` and cover:
- **LocaleChainTest.cpp** -- API tests (Configure, Resolve, GetChain, Reset, edge cases)
- **FallbackMapTest.cpp** -- Fallback data integrity (group presence, chain values, merge operations)

## Packaging for Distribution

Package the plugin as a standalone distributable using `RunUAT BuildPlugin`. This produces a folder with pre-compiled binaries that users can drop into their project without building from source.

### Packaging for a Single UE Version

```bash
# Windows -- UE 5.3, Win64
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.3-Win64" \
  -TargetPlatforms=Win64 \
  -Rocket

# Mac -- UE 5.3, Mac
/Users/Shared/Epic\ Games/UE_5.3/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin \
  -Plugin="/Users/you/Projects/YourProject/Plugins/LocaleChain/LocaleChain.uplugin" \
  -Package="/Users/you/Output/LocaleChain-UE5.3-Mac" \
  -TargetPlatforms=Mac \
  -Rocket
```

### Packaging for All Supported UE Versions

Repeat for each engine version you want to support:

#### UE 5.3

```bash
# Windows
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.3-Win64" \
  -TargetPlatforms=Win64 \
  -Rocket

# Mac
/Users/Shared/Epic\ Games/UE_5.3/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin \
  -Plugin="/Users/you/Projects/YourProject/Plugins/LocaleChain/LocaleChain.uplugin" \
  -Package="/Users/you/Output/LocaleChain-UE5.3-Mac" \
  -TargetPlatforms=Mac \
  -Rocket

# Linux (cross-compile from Windows/Mac, or build on Linux)
# Requires Linux cross-compilation toolchain installed in UE
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.3-Linux" \
  -TargetPlatforms=Linux \
  -Rocket
```

#### UE 5.4

```bash
# Windows
"C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.4-Win64" \
  -TargetPlatforms=Win64 \
  -Rocket

# Mac
/Users/Shared/Epic\ Games/UE_5.4/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin \
  -Plugin="/Users/you/Projects/YourProject/Plugins/LocaleChain/LocaleChain.uplugin" \
  -Package="/Users/you/Output/LocaleChain-UE5.4-Mac" \
  -TargetPlatforms=Mac \
  -Rocket

# Linux
"C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.4-Linux" \
  -TargetPlatforms=Linux \
  -Rocket
```

#### UE 5.5

```bash
# Windows
"C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.5-Win64" \
  -TargetPlatforms=Win64 \
  -Rocket

# Mac
/Users/Shared/Epic\ Games/UE_5.5/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin \
  -Plugin="/Users/you/Projects/YourProject/Plugins/LocaleChain/LocaleChain.uplugin" \
  -Package="/Users/you/Output/LocaleChain-UE5.5-Mac" \
  -TargetPlatforms=Mac \
  -Rocket

# Linux
"C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin \
  -Plugin="C:\Projects\YourProject\Plugins\LocaleChain\LocaleChain.uplugin" \
  -Package="C:\Output\LocaleChain-UE5.5-Linux" \
  -TargetPlatforms=Linux \
  -Rocket
```

## Creating a GitHub Release

After packaging, create a GitHub Release with the pre-built binaries:

### 1. Zip Each Package

```bash
# Example for all UE 5.3 platforms
cd C:\Output
tar -czf LocaleChain-v1.0.0-UE5.3-Win64.zip LocaleChain-UE5.3-Win64/
tar -czf LocaleChain-v1.0.0-UE5.3-Mac.zip LocaleChain-UE5.3-Mac/
tar -czf LocaleChain-v1.0.0-UE5.3-Linux.zip LocaleChain-UE5.3-Linux/

# Repeat for UE 5.4 and 5.5
```

### 2. Create the Release

```bash
gh release create v1.0.0 \
  --title "v1.0.0" \
  --notes "Initial release. See CHANGELOG.md for details." \
  LocaleChain-v1.0.0-UE5.3-Win64.zip \
  LocaleChain-v1.0.0-UE5.3-Mac.zip \
  LocaleChain-v1.0.0-UE5.3-Linux.zip \
  LocaleChain-v1.0.0-UE5.4-Win64.zip \
  LocaleChain-v1.0.0-UE5.4-Mac.zip \
  LocaleChain-v1.0.0-UE5.4-Linux.zip \
  LocaleChain-v1.0.0-UE5.5-Win64.zip \
  LocaleChain-v1.0.0-UE5.5-Mac.zip \
  LocaleChain-v1.0.0-UE5.5-Linux.zip
```

### Release Asset Naming Convention

```
LocaleChain-v{VERSION}-UE{ENGINE_VERSION}-{PLATFORM}.zip
```

Expected assets for a full release:
- `LocaleChain-v1.0.0-UE5.3-Win64.zip`
- `LocaleChain-v1.0.0-UE5.3-Mac.zip`
- `LocaleChain-v1.0.0-UE5.3-Linux.zip`
- `LocaleChain-v1.0.0-UE5.4-Win64.zip`
- `LocaleChain-v1.0.0-UE5.4-Mac.zip`
- `LocaleChain-v1.0.0-UE5.4-Linux.zip`
- `LocaleChain-v1.0.0-UE5.5-Win64.zip`
- `LocaleChain-v1.0.0-UE5.5-Mac.zip`
- `LocaleChain-v1.0.0-UE5.5-Linux.zip`

## Troubleshooting

**"Plugin not found" after cloning:**
Make sure the plugin folder is named `LocaleChain` (matching the module name) and is directly inside your project's `Plugins/` directory. Regenerate project files after adding the plugin.

**Build errors about missing headers:**
Ensure your `.uproject` or `.Build.cs` includes `"LocaleChain"` in its module dependencies if you are referencing the plugin's classes directly.

**Tests not appearing in Automation tab:**
Tests are registered under the `LocaleChain.*` prefix. Make sure you are running an Editor build (not a cooked/packaged build) and the plugin is enabled in your project.

**Linux cross-compilation fails:**
Install the Linux cross-compilation toolchain via the Epic Games Launcher under Engine > Options > Target Platforms > Linux.
