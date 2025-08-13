Write-Host "🎮 Installing Terminal Pong for Windows..." -ForegroundColor Cyan

$downloadUrl = "https://github.com/TomDevX/terminal-pong/archive/refs/tags/v4.zip"
$tempZip = "$env:TEMP\terminal-pong.zip"
Invoke-WebRequest -Uri $downloadUrl -OutFile $tempZip

$installDir = "$env:USERPROFILE\terminal-pong"
if (Test-Path $installDir) { Remove-Item $installDir -Recurse -Force }
Expand-Archive -Path $tempZip -DestinationPath $installDir

$exePath = Get-ChildItem -Path $installDir -Recurse -Filter "terminal-pong.exe" | Select-Object -First 1
if ($exePath) {
    Write-Host "🚀 Launching Terminal Pong..." -ForegroundColor Green
    Start-Process $exePath.FullName
} else {
    Write-Host "⚠️ Game executable not found. Please check installation." -ForegroundColor Red
}

Remove-Item $tempZip -Force

Write-Host "✅ Installation complete!" -ForegroundColor Green
