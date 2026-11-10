# Obsid1an

Semi-untethered jailbreak for iOS 27.0 — 27.0.1.

## Status

In development — exploit payload pending release from [calif.io](https://calif.io).

## Structure

```
app/        iOS jailbreak app (SwiftUI + Xcode)
repo/       APT package repository (repo.obsid1an.app)
site/       Project website (obsid1an.app)
```

## App

The jailbreak app handles the full chain: exploit execution, bootstrap installation, package management setup, and post-jailbreak tools.

```
app/Obsid1an/
  App/          Entry point
  Views/        Jailbreak UI, settings panel
  Exploit/      Exploit pipeline, calif.io integration
  System/       Respring, userspace reboot, settings persistence
  Bootstrap/    Bootstrap extraction, repo config, dpkg/apt setup
  Resources/    Assets, icon, build config
```

**What works now:** UI, exploit simulation, settings persistence, log export.
**What needs root:** Respring, tweak flag files, icon cache, bootstrap install.
**What needs the exploit:** The actual jailbreak.

## Repository

The APT repo at `repo.obsid1an.app` serves packages to Sileo and Zebra. Includes web depictions with auto device/version compatibility detection and a browser-based package listing.

```
repo/
  depictions/   Tweak pages (HTML for Zebra, JSON for Sileo native)
  debs/         .deb packages
  assets/       Tweak icons and screenshots
  Packages      APT manifest
  Release       Repo metadata
```

## Building

1. Open `app/Obsid1an.xcodeproj` in Xcode 26.5+
2. Set your signing team under Signing & Capabilities
3. Build and run on device

## Requirements

- iOS 27.0 or 27.0.1
- Xcode 26.5+
- Personal Apple ID signing

## Credits

- [Kilian Balaguer](https://github.com/kilianbalaguer) — Developer
- [calif.io](https://calif.io) — Kernel exploit
- [ElleKit](https://github.com/evelyneee/ellekit) — Tweak injection
- [Procursus](https://github.com/ProcursusTeam/Procursus) — Bootstrap
