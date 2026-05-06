# Rainmeter Codex Halo

$ErrorActionPreference = 'Stop'

$source = Split-Path -Parent $MyInvocation.MyCommand.Path
$target = Join-Path $HOME 'Documents\Rainmeter\Skins\Rainmeter Codex Halo'

if (-not (Test-Path -LiteralPath $target)) {
    New-Item -ItemType Directory -Force -Path $target | Out-Null
}

$rainmeter = Join-Path ${env:ProgramFiles} 'Rainmeter\Rainmeter.exe'
if (Test-Path -LiteralPath $rainmeter) {
    Start-Process -FilePath $rainmeter -ArgumentList '!DeactivateConfig "Rainmeter Codex Halo"' -WindowStyle Hidden -Wait
    Start-Process -FilePath $rainmeter -ArgumentList '!DeactivateConfig "Rainmeter Codex Halo\Welcome"' -WindowStyle Hidden -Wait
    Start-Process -FilePath $rainmeter -ArgumentList '!DeactivateConfig "Rainmeter Codex Halo\Halo"' -WindowStyle Hidden -Wait
}

Get-ChildItem -LiteralPath $source -Force | ForEach-Object {
    Copy-Item -LiteralPath $_.FullName -Destination $target -Recurse -Force
}

if (Test-Path -LiteralPath $rainmeter) {
    Start-Process -FilePath $rainmeter -ArgumentList '!Refresh "Rainmeter Codex Halo"' -WindowStyle Hidden -Wait
    Start-Process -FilePath $rainmeter -ArgumentList '!ActivateConfig "Rainmeter Codex Halo\Welcome" "Welcome.ini"' -WindowStyle Hidden
}

Write-Host "Installed Codex Halo to $target"
