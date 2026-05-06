# Codex Halo Rainmeter Skin

This is a Rainmeter design system for the Codex 5h and weekly rate-limit counters. It includes a circular Halo Pro instrument, a horizontal desk-bar layout, a vertical stacked layout, a low-text Glyph meter, and a control panel for switching designs and sizes.

## Project Owner

Peter owns this project and public attribution points to [https://github.com/PetersMinistry](https://github.com/PetersMinistry). Codex is the lead developer/maintainer for this skin.

## Files

- `CodexHalo.ini` is the standard Rainmeter skin.
- `CodexHalo Compact.ini` is the compact size.
- `CodexHalo Large.ini` is the large size.
- `Control/Settings.ini` is the design and size selector.
- `Horizontal/Compact.ini`, `Horizontal/Standard.ini`, and `Horizontal/Large.ini` are the wide layouts.
- `Vertical/Compact.ini`, `Vertical/Standard.ini`, and `Vertical/Large.ini` are the stacked layouts.
- `Glyph/Compact.ini`, `Glyph/Standard.ini`, and `Glyph/Large.ini` are the low-text circular meter layouts.
- `@Resources/CodexLimits.inc` stores the displayed values as Rainmeter variables.
- `@Resources/Options.inc` keeps user-editable options in the same addon folder.
- `@Resources/Layouts/HaloPro.inc` is the shared Halo Pro layout used by all size variants.
- `@Resources/Layouts/HorizontalPro.inc` is the shared wide layout.
- `@Resources/Layouts/VerticalPro.inc` is the shared stacked layout.
- `@Resources/Layouts/GlyphPro.inc` is the shared twin circular meter layout.
- `@Resources/Scripts/Update-CodexLimits.ps1` reads the latest Codex session rate-limit event and refreshes the include file. The skin calls it once an hour by default and when the status pill is clicked.
- `Install-To-Rainmeter.ps1` can reinstall this folder into the standard Rainmeter skins location if the project is copied elsewhere.

## Install

Copy or clone this folder into the standard Rainmeter skins folder:

```text
%USERPROFILE%\Documents\Rainmeter\Skins\Rainmeter Codex Halo
```

In Rainmeter, refresh all skins and load one of:

```text
Rainmeter Codex Halo\Control\Settings.ini
Rainmeter Codex Halo\CodexHalo Compact.ini
Rainmeter Codex Halo\CodexHalo.ini
Rainmeter Codex Halo\CodexHalo Large.ini
Rainmeter Codex Halo\Horizontal\Compact.ini
Rainmeter Codex Halo\Horizontal\Standard.ini
Rainmeter Codex Halo\Horizontal\Large.ini
Rainmeter Codex Halo\Vertical\Compact.ini
Rainmeter Codex Halo\Vertical\Standard.ini
Rainmeter Codex Halo\Vertical\Large.ini
Rainmeter Codex Halo\Glyph\Compact.ini
Rainmeter Codex Halo\Glyph\Standard.ini
Rainmeter Codex Halo\Glyph\Large.ini
```

If the folder is edited from a different staging location, run `Install-To-Rainmeter.ps1` from that staging folder to copy it into the current user's Rainmeter skins folder and reload the default Halo skin.

## Switching Designs

Load `Rainmeter Codex Halo\Control\Settings.ini` for the full selector panel.

Every loadable skin also adds a short native Rainmeter right-click quick menu:

- `Open Codex Halo Control`
- `Refresh Codex Data`

Use the Control panel when you want exact design and size choices like compact, standard, or large. The native right-click menu intentionally stays at two custom actions so Rainmeter does not move it into an extra `Custom skin actions` submenu. Rainmeter's built-in Variants and root-config menus remain available for normal skin loading.

The Control panel has a small `X` button in the top-right corner. It closes only the Control panel and leaves the currently selected display skin running.

## Current Data Source

The current version reads Codex's local session event stream from the current Windows user's Codex data folder, computes remaining percent from the reported used percent, updates `LastChecked`, and labels the display as `live event` when that read succeeds. If no current rate-limit event can be found, it keeps the last known values and labels them as `cached snapshot`.

The current bucket is valid until the reset time/date from Codex. The 5h window usually has a time such as `10:58 PM`; if it crosses midnight, the updater can include the date too. The weekly window has the reset date, such as `May 11`.

The Codex menu itself is still not scraped directly. OCR/UI automation remains a fallback path only if the local event stream stops exposing `rate_limits`.

- UI automation that opens/reads the Codex account menu.
- OCR against a small screenshot of the rate-limit menu.
- An internal Codex state/API reader if one becomes identifiable.

## Styling Notes

The Halo design keeps the pet in the center with 5h as the outer green ring and weekly as the inner blue ring. The wide design is a compact horizontal status bar for top/bottom desktop placement. The stacked design is a narrow vertical console for side placement. The Glyph design is the most graphic-centric option: twin circular meters, centered numbers, short labels, and a click-to-refresh status dot. Display faces keep reset/check details out of the metric blocks; hover the values, bars, cards, or status areas for reset/check tooltips.
