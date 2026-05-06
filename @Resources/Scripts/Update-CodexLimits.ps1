# Rainmeter Codex Halo

param(
    [string]$OutputPath = "$PSScriptRoot\..\CodexLimits.inc"
)

$default = [ordered]@{
    FiveHourValue = '100'
    FiveHourReset = 'pending'
    WeeklyValue   = '100'
    WeeklyReset   = 'pending'
    LastChecked   = 'never'
    DataStatus    = 'cached snapshot'
}

function Read-LimitFile {
    param([string]$Path)

    $values = [ordered]@{}
    foreach ($key in $default.Keys) {
        $values[$key] = $default[$key]
    }

    if (Test-Path -LiteralPath $Path) {
        Get-Content -LiteralPath $Path | ForEach-Object {
            if ($_ -match '^\s*([^=\[\];]+?)\s*=\s*(.*?)\s*$') {
                $values[$matches[1]] = $matches[2]
            }
        }
    }

    return $values
}

function Convert-UnixToLocal {
    param([double]$UnixTime)

    return ([DateTimeOffset]::FromUnixTimeSeconds([Int64][Math]::Round($UnixTime))).LocalDateTime
}

function Format-Reset {
    param(
        [DateTime]$ResetTime,
        [int]$WindowMinutes
    )

    if ($WindowMinutes -ge 1440) {
        return $ResetTime.ToString('MMM d')
    }

    if ($ResetTime.Date -ne (Get-Date).Date) {
        return $ResetTime.ToString('MMM d h:mm tt')
    }

    return $ResetTime.ToString('h:mm tt')
}

function Convert-PercentRemaining {
    param($UsedPercent)

    $used = [double]$UsedPercent
    $remaining = [int][Math]::Round(100 - $used)

    if ($remaining -lt 0) {
        return 0
    }

    if ($remaining -gt 100) {
        return 100
    }

    return $remaining
}

function Get-CodexRoot {
    if ($env:CODEX_HOME -and (Test-Path -LiteralPath $env:CODEX_HOME)) {
        return $env:CODEX_HOME
    }

    $homeRoot = Join-Path $HOME '.codex'
    if (Test-Path -LiteralPath $homeRoot) {
        return $homeRoot
    }

    return $null
}

function Read-RateLimitFromLine {
    param([string]$Line)

    try {
        $event = $Line | ConvertFrom-Json -ErrorAction Stop
    }
    catch {
        return $null
    }

    $limits = $event.rate_limits
    if (-not $limits -and $event.payload) {
        $limits = $event.payload.rate_limits
    }

    if (-not $limits -or -not $limits.primary -or -not $limits.secondary) {
        return $null
    }

    if ($limits.limit_id -ne 'codex') {
        return $null
    }

    $primary = $limits.primary
    $secondary = $limits.secondary
    $eventTime = [DateTimeOffset]::Parse($event.timestamp).LocalDateTime

    return [pscustomobject]@{
        EventTime = $eventTime
        FiveHourValue = (Convert-PercentRemaining $primary.used_percent)
        FiveHourReset = (Format-Reset (Convert-UnixToLocal $primary.resets_at) ([int]$primary.window_minutes))
        WeeklyValue = (Convert-PercentRemaining $secondary.used_percent)
        WeeklyReset = (Format-Reset (Convert-UnixToLocal $secondary.resets_at) ([int]$secondary.window_minutes))
    }
}

function Get-TailLines {
    param(
        [string]$Path,
        [int]$MaxBytes = 4194304
    )

    try {
        $stream = [System.IO.File]::Open($Path, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite)
        try {
            $bytesToRead = [Math]::Min($MaxBytes, [int]$stream.Length)
            if ($bytesToRead -le 0) {
                return @()
            }

            [void]$stream.Seek(-1 * $bytesToRead, [System.IO.SeekOrigin]::End)
            $buffer = New-Object byte[] $bytesToRead
            $read = $stream.Read($buffer, 0, $bytesToRead)
            $text = [System.Text.Encoding]::UTF8.GetString($buffer, 0, $read)
            return ($text -split '\r?\n') | Where-Object { $_ }
        }
        finally {
            $stream.Dispose()
        }
    }
    catch {
        return @()
    }
}

function Get-LatestCodexRateLimits {
    $codexRoot = Get-CodexRoot
    if (-not $codexRoot) {
        return $null
    }

    $sessionRoot = Join-Path $codexRoot 'sessions'
    if (-not (Test-Path -LiteralPath $sessionRoot)) {
        return $null
    }

    $today = Get-Date
    $yesterday = $today.AddDays(-1)
    function Join-SessionDatePath {
        param([DateTime]$Date)

        return (Join-Path $sessionRoot (Join-Path $Date.ToString('yyyy') (Join-Path $Date.ToString('MM') $Date.ToString('dd'))))
    }

    $searchRoots = @(
        (Join-SessionDatePath $today),
        (Join-SessionDatePath $yesterday)
    ) | Where-Object { Test-Path -LiteralPath $_ }

    if (-not $searchRoots) {
        $searchRoots = @($sessionRoot)
    }

    $files = foreach ($root in $searchRoots) {
        Get-ChildItem -LiteralPath $root -File -Filter '*.jsonl' -ErrorAction SilentlyContinue
    }

    $candidates = @($files) |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 5

    $latest = $null

    foreach ($file in $candidates) {
        $lines = @(Get-TailLines -Path $file.FullName | Where-Object { $_ -like '*"rate_limits"*' })

        for ($i = $lines.Count - 1; $i -ge 0; $i--) {
            $reading = Read-RateLimitFromLine -Line $lines[$i]
            if (-not $reading) {
                continue
            }

            if (-not $latest -or $reading.EventTime -gt $latest.EventTime) {
                $latest = $reading
            }

            break
        }
    }

    return $latest
}

$resolvedOutput = $ExecutionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($OutputPath)
$outputDir = Split-Path -Parent $resolvedOutput
if (-not (Test-Path -LiteralPath $outputDir)) {
    New-Item -ItemType Directory -Force -Path $outputDir | Out-Null
}

$values = Read-LimitFile -Path $resolvedOutput

$reading = Get-LatestCodexRateLimits

if ($reading) {
    $values['FiveHourValue'] = [string]$reading.FiveHourValue
    $values['FiveHourReset'] = $reading.FiveHourReset
    $values['WeeklyValue'] = [string]$reading.WeeklyValue
    $values['WeeklyReset'] = $reading.WeeklyReset
    $values['DataStatus'] = 'live event'
}
else {
    $values['DataStatus'] = 'cached snapshot'
}

$values['LastChecked'] = Get-Date -Format 'h:mm tt'

$lines = New-Object System.Collections.Generic.List[string]
$lines.Add('; Rainmeter Codex Halo')
$lines.Add('[Variables]')
foreach ($key in @('FiveHourValue', 'FiveHourReset', 'WeeklyValue', 'WeeklyReset', 'LastChecked', 'DataStatus')) {
    $lines.Add("$key=$($values[$key])")
}

Set-Content -LiteralPath $resolvedOutput -Value $lines -Encoding ASCII
