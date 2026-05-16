# Changelog

## 0.5.15

- Restores the local Codex `rate_limits` event stream as the first-choice source because it matches the visible Codex app panel.
- Keeps the web usage endpoint as fallback only, avoiding mismatches when the bearer-token usage response shows a different reset bucket.
- Marks event-sourced cache reads as `live event` so the 30-second refresh guard still prevents overlapping updater launches.

## 0.5.14

- Follows the visible Codex account usage row first instead of the extra model-specific row, matching the app menu when both are present.
- Allows live account usage to replace an older cached model-specific reset window, preventing the skin from staying on `May 23` when Codex shows `May 18`.
- Treats near-full 5-hour usage as `100%` remaining to match the Codex menu display.

## 0.5.13

- Adds reset-epoch tracking to the shared Codex cache so the updater can detect and reject stale source regressions.
- Chooses the usage row with the latest weekly reset, preferring active additional model rows over the stale root row when both are present.
- Keeps the last app-backed cache if a fallback source reports an older 5-hour or weekly reset, preventing the skin from dropping back to old numbers after a reset.

## 0.5.12

- Reads the same Codex usage source as the app account menu and prefers the active additional model limit when present, fixing stale percentages after account resets.
- Adds a small Node.js helper for the live usage request, avoiding the Windows PowerShell TLS path that can fail against the Codex usage endpoint on this machine.
- Keeps previously good usage values cached if the live request fails, instead of overwriting them with stale legacy event data.
- Splits manual refreshes from automatic timer refreshes, routes automatic refreshes through the Lua elapsed-time guard, and adds a shared updater lock so refreshes cannot stack up or write the limit cache at the same time.
- Adds a short cache-age guard inside the updater, so accidental extra Rainmeter launches do not repeatedly call the usage endpoint or rewrite the shared cache.

## 0.5.11

- Tightens Codex limit refresh behavior to reduce visible drift from the Codex panel: default refresh interval is now 30 seconds.
- Replaces the old separate auto RunCommand path across display layouts with one guarded refresh timer that calls the shared Lua helper.
- Adds stale `RefreshBusy` recovery so a missed RunCommand finish callback cannot leave the skin stuck on old values.

## 0.5.10

- Quieted Rainmeter log spam from MicroStack by updating only measures that exist in the active skin.
- Changed MicroStack startup behavior to read cached values first and guard refresh launches, preventing overlapping RunCommand notices.

## 0.5.9

- Forces a data refresh when Codex Halo skins are loaded or refreshed, preventing stale loaded values from sitting on screen.
- Updates the Lua readback helper to refresh the rail measurements used by Signal Rail and Micro Stack.

## 0.5.8

- Searches recently modified Codex session files across the full session tree, so long-running sessions stored under older date folders still provide live rate-limit data.

## 0.5.7

- Treats Codex reset timestamps as authoritative so expired windows roll forward instead of displaying stale event percentages.

## 0.5.6

- Added `Streamline/Standard.ini`, a compact thin horizontal display with visible 5-hour end time and weekly reset date.
- Added Streamline to the Control panel as a one-click thin horizontal template.
- Added refined `SignalRail/Standard.ini` and `MicroStack/Standard.ini` concept skins using Bahnschrift and Cascadia Mono.
- Removed the visible style-name labels from Signal Rail and Micro Stack so the new designs stay cleaner on desktop.

## 0.5.5

- Removed hard-coded display layer settings so Rainmeter's native Position menu owns Stay topmost, Topmost, Normal, Bottom, and On desktop behavior.
- Replaced the 5-minute timer skin reload with an in-memory Lua reread of `CodexLimits.inc`, keeping local rate-limit values current without disturbing Rainmeter's saved position/layer state.
- Updated Control and Welcome refresh actions to use the same local reread path instead of refreshing every Codex Halo display config.

## 0.5.4

- Fixed unattended 5-minute refresh so active display skins reread `CodexLimits.inc` after the local updater writes fresh values.
- Applies to Halo, Horizontal, Vertical, and Glyph layouts.
- Uses a current-config refresh instead of a global Rainmeter refresh to avoid desktop jitter.

## 0.5.3

- Reduced Glyph value text sizes across Compact, Standard, and Large layouts so `100%` fits cleanly inside the circular meters without crowding the ring lines.

## 0.5.2

- Changed the default refresh interval from hourly to every 5 minutes.
- Reworked automatic refresh to update values in place instead of reloading the skin, reducing drag jitter and helping Bottom positioning stay stable.
- Made display skins explicitly use Rainmeter's Bottom layer.
- Improved Halo manual refresh targets so the lower metric console, values, bars, and footer can refresh the snapshot directly.

## 0.5.1

- Fixed Rainmeter variable parsing for the local Codex limit cache.
- Updated `@Resources/CodexLimits.inc` so it is written as a proper `[Variables]` include.
- Added public README screenshots for the control panel and all display styles.
- Simplified the README and moved release details here.

## 0.5.0

- Reorganized Codex Halo into a standard Rainmeter suite structure.
- Added the Welcome launcher flow.
- Added the Control panel for choosing design and size.
- Added four display families: Halo, Horizontal, Vertical, and Glyph.
- Added native Rainmeter right-click actions for opening Control and refreshing Codex data.
- Normalized public metadata and license fields across loadable pieces.

## Notes

Codex Halo prefers Codex's own usage endpoint so it can match the app account menu. Legacy local `rate_limits` session events are kept only as a fallback.