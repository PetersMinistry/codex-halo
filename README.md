# Codex Halo

<p align="center">
  <img src="docs/cover.png" alt="Codex Halo Rainmeter skin cover" width="900">
</p>

<p align="center">
  <strong>A Rainmeter skin for local Codex rate-limit status.</strong><br>
  See your 5-hour and weekly Codex limits at a glance, right on the Windows desktop.
</p>

<p align="center">
  <a href="#install">Install</a> |
  <a href="#designs">Designs</a> |
  <a href="#privacy">Privacy</a> |
  <a href="CHANGELOG.md">Changelog</a>
</p>

## Preview

<p align="center">
  <img src="docs/screenshots/control-panel.png" alt="Codex Halo control panel" width="430">
</p>

<table>
  <tr>
    <td align="center"><img src="docs/screenshots/halo-standard.png" alt="Halo design" width="260"><br><strong>Halo</strong></td>
    <td align="center"><img src="docs/screenshots/horizontal-standard.png" alt="Horizontal design" width="320"><br><strong>Horizontal</strong></td>
  </tr>
  <tr>
    <td align="center"><img src="docs/screenshots/vertical-compact.png" alt="Vertical design" width="220"><br><strong>Vertical</strong></td>
    <td align="center"><img src="docs/screenshots/glyph-standard.png" alt="Glyph design" width="280"><br><strong>Glyph</strong></td>
  </tr>
</table>

## Features

- Shows Codex 5-hour and weekly limit remaining
- Includes reset time/date and last local refresh time
- Four display styles with multiple sizes
- Control panel for switching layouts
- Manual refresh from the skin or Rainmeter right-click menu
- Local-only data reading, with no external API call

## Requirements

- Windows
- Rainmeter
- Codex installed and writing local session logs
- PowerShell, included with Windows

## Install

Copy this folder to:

```text
%USERPROFILE%\Documents\Rainmeter\Skins\Rainmeter Codex Halo
```

In Rainmeter, refresh skins and load:

```text
Rainmeter Codex Halo\Welcome\Welcome.ini
```

Click **Start Halo** to refresh the local Codex snapshot and open the main skin.

## Designs

Use the control panel to switch designs and sizes:

```text
Rainmeter Codex Halo\Control\Settings.ini
```

Available designs:

- `Halo` - circular ring display
- `Horizontal` - wide compact bar
- `Vertical` - stacked compact panel
- `Glyph` - minimal twin-meter display

## Refresh

Click the skin's status pill, or use the Rainmeter right-click menu:

```text
Refresh Codex Data
```

The current values are stored locally in:

```text
@Resources\CodexLimits.inc
```

## Privacy

Codex Halo reads local Codex session files from the current Windows user. It does not scrape the web, call a hosted API, or send your usage data anywhere.

Compatibility depends on Codex writing local `rate_limits` events in its session logs. If no current event is found, Codex Halo keeps the last cached values.

## Version

Current build: `0.5.2`

See [CHANGELOG.md](CHANGELOG.md) for release notes.

## Credits

Created by [PetersMinistry](https://github.com/PetersMinistry).

Released under the MIT License.
