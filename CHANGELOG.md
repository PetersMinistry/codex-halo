# Changelog

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
- Normalized public metadata to `Author=PetersMinistry` and `License=MIT`.

## Notes

Codex Halo reads local Codex session logs only. It does not call an external API. Compatibility depends on Codex continuing to write local `rate_limits` events.
