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

function Get-LimitWindowState {
    param(
        $UsedPercent,
        [double]$ResetsAt,
        [int]$WindowMinutes
    )

    $resetTime = Convert-UnixToLocal $ResetsAt
    $now = Get-Date

    if ($WindowMinutes -gt 0 -and $resetTime -le $now) {
        do {
            $resetTime = $resetTime.AddMinutes($WindowMinutes)
        } while ($resetTime -le $now)

        return [pscustomobject]@{
            Remaining = 100
            Reset     = (Format-Reset $resetTime $WindowMinutes)
        }
    }

    return [pscustomobject]@{
        Remaining = (Convert-PercentRemaining $UsedPercent)
        Reset     = (Format-Reset $resetTime $WindowMinutes)
    }
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

function Get-NodeExecutable {
    foreach ($name in @('node.exe', 'node')) {
        $command = Get-Command $name -ErrorAction SilentlyContinue
        if ($command -and $command.Source) {
            return $command.Source
        }
    }

    return $null
}

function Get-UsageWindowState {
    param($Window)

    if (-not $Window) {
        return $null
    }

    $usedPercent = $Window.used_percent
    $resetsAt = $Window.reset_at
    $windowSeconds = $Window.limit_window_seconds

    if ($null -eq $usedPercent -or $null -eq $resetsAt) {
        return $null
    }

    $windowMinutes = 0
    if ($windowSeconds) {
        $windowMinutes = [int][Math]::Round(([double]$windowSeconds) / 60)
    }

    return Get-LimitWindowState $usedPercent ([double]$resetsAt) $windowMinutes
}

function Get-LatestCodexUsage {
    $node = Get-NodeExecutable
    if (-not $node) {
        return $null
    }

    $helperPath = Join-Path $PSScriptRoot 'Fetch-CodexUsage.js'
    if (-not (Test-Path -LiteralPath $helperPath)) {
        return $null
    }

    try {
        $processInfo = New-Object System.Diagnostics.ProcessStartInfo
        $processInfo.FileName = $node
        $processInfo.Arguments = '"' + $helperPath.Replace('"', '\"') + '"'
        $processInfo.UseShellExecute = $false
        $processInfo.RedirectStandardOutput = $true
        $processInfo.RedirectStandardError = $true
        $processInfo.CreateNoWindow = $true

        $process = [System.Diagnostics.Process]::Start($processInfo)
        if (-not $process.WaitForExit(20000)) {
            try {
                $process.Kill()
            }
            catch {
            }

            return $null
        }

        if ($process.ExitCode -ne 0) {
            return $null
        }

        $payload = $process.StandardOutput.ReadToEnd()
        if (-not $payload) {
            return $null
        }

        $usage = $payload | ConvertFrom-Json -ErrorAction Stop
        $primaryState = Get-UsageWindowState $usage.primary
        $secondaryState = Get-UsageWindowState $usage.secondary

        if (-not $primaryState -or -not $secondaryState) {
            return $null
        }

        return [pscustomobject]@{
            EventTime = Get-Date
            FiveHourValue = $primaryState.Remaining
            FiveHourReset = $primaryState.Reset
            WeeklyValue = $secondaryState.Remaining
            WeeklyReset = $secondaryState.Reset
        }
    }
    catch {
        return $null
    }
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
    $primaryState = Get-LimitWindowState $primary.used_percent $primary.resets_at ([int]$primary.window_minutes)
    $secondaryState = Get-LimitWindowState $secondary.used_percent $secondary.resets_at ([int]$secondary.window_minutes)

    return [pscustomobject]@{
        EventTime = $eventTime
        FiveHourValue = $primaryState.Remaining
        FiveHourReset = $primaryState.Reset
        WeeklyValue = $secondaryState.Remaining
        WeeklyReset = $secondaryState.Reset
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

    $dateRoots = @(
        (Join-SessionDatePath $today),
        (Join-SessionDatePath $yesterday)
    ) | Where-Object { Test-Path -LiteralPath $_ }

    $dateFiles = foreach ($root in $dateRoots) {
        Get-ChildItem -LiteralPath $root -File -Filter '*.jsonl' -ErrorAction SilentlyContinue
    }

    $recentFiles = Get-ChildItem -LiteralPath $sessionRoot -Recurse -File -Filter '*.jsonl' -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 10

    $candidates = @($dateFiles) + @($recentFiles) |
        Where-Object { $_ } |
        Group-Object FullName |
        ForEach-Object { $_.Group[0] } |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 10

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

$lockStream = $null
$lockPath = Join-Path $outputDir 'CodexLimits.update.tmp'
try {
    $lockStream = [System.IO.File]::Open($lockPath, [System.IO.FileMode]::OpenOrCreate, [System.IO.FileAccess]::ReadWrite, [System.IO.FileShare]::None)
}
catch {
    return
}

try {
$values = Read-LimitFile -Path $resolvedOutput

if (Test-Path -LiteralPath $resolvedOutput) {
    $cacheAge = (Get-Date) - (Get-Item -LiteralPath $resolvedOutput).LastWriteTime
    if (
        $cacheAge.TotalSeconds -lt 30 -and
        ($values['DataStatus'] -eq 'live usage' -or $values['DataStatus'] -eq 'cached usage')
    ) {
        return
    }
}

$reading = Get-LatestCodexUsage

if ($reading) {
    $values['FiveHourValue'] = [string]$reading.FiveHourValue
    $values['FiveHourReset'] = $reading.FiveHourReset
    $values['WeeklyValue'] = [string]$reading.WeeklyValue
    $values['WeeklyReset'] = $reading.WeeklyReset
    $values['DataStatus'] = 'live usage'
}
else {
    if ($values['DataStatus'] -eq 'live usage' -or $values['DataStatus'] -eq 'cached usage') {
        $values['DataStatus'] = 'cached usage'
    }
    else {
        $reading = Get-LatestCodexRateLimits

        if ($reading) {
            $values['FiveHourValue'] = [string]$reading.FiveHourValue
            $values['FiveHourReset'] = $reading.FiveHourReset
            $values['WeeklyValue'] = [string]$reading.WeeklyValue
            $values['WeeklyReset'] = $reading.WeeklyReset
            $values['DataStatus'] = 'legacy event'
        }
        else {
            $values['DataStatus'] = 'cached snapshot'
        }
    }
}

$values['LastChecked'] = Get-Date -Format 'h:mm tt'

$lines = New-Object System.Collections.Generic.List[string]
$lines.Add('; Rainmeter Codex Halo')
$lines.Add('[Variables]')
foreach ($key in @('FiveHourValue', 'FiveHourReset', 'WeeklyValue', 'WeeklyReset', 'LastChecked', 'DataStatus')) {
    $lines.Add("$key=$($values[$key])")
}

Set-Content -LiteralPath $resolvedOutput -Value $lines -Encoding ASCII
}
finally {
    if ($lockStream) {
        $lockStream.Dispose()
    }
}
