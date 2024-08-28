# PowerShell Script to Check and Install xmake on Windows

# Check if xmake is installed
if (-not (Get-Command xmake -ErrorAction SilentlyContinue)) {
    Write-Host "xmake is not installed. Installing xmake..."
    # Install xmake
    Invoke-Expression (Invoke-WebRequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
} else {
    Write-Host "xmake is already installed."
}
