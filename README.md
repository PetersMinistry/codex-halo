# Codex Halo

Codex Halo is a Rainmeter skin for showing local Codex rate-limit status on your Windows desktop.

It displays:

- 5-hour limit remaining
- Weekly limit remaining
- Reset time/date
- Last local refresh time

## Requirements

- Windows
- Rainmeter
- Codex installed and writing local session logs
- PowerShell, included with Windows

Codex Halo reads local Codex session files only. It does not call an external API.

## Preview

![Codex Halo control panel](docs/screenshots/control-panel.png)

![Halo design](docs/screenshots/halo-standard.png)

![Horizontal design](docs/screenshots/horizontal-standard.png)

![Vertical design](docs/screenshots/vertical-compact.png)

![Glyph design](docs/screenshots/glyph-standard.png)

## Install

Copy this folder to:

```text
%USERPROFILE%\Documents\Rainmeter\Skins\Rainmeter Codex Halo
```

Then open Rainmeter, refresh skins, and load:

```text
Rainmeter Codex Halo\Welcome\Welcome.ini
```

Click **Start Halo** to refresh the local Codex snapshot and open the main skin.

## Designs

Codex Halo includes four display styles:

- `Halo` - circular ring display
- `Horizontal` - wide compact bar
- `Vertical` - stacked compact panel
- `Glyph` - minimal twin-meter display

Use:

```text
Rainmeter Codex Halo\Control\Settings.ini
```

to switch designs and sizes.

## Refreshing

Click the status pill or use the right-click menu item:

```text
Refresh Codex Data
```

The skin refreshes from local Codex session data and stores the current values in:

```text
@Resources\CodexLimits.inc
```

## Notes

Compatibility depends on Codex writing local `rate_limits` events in its session logs. If no current event is found, the skin keeps the last cached values.

## Version

Current build: `0.5.1`

## Credits

Created by [PetersMinistry](https://github.com/PetersMinistry).

Released under the MIT License.
