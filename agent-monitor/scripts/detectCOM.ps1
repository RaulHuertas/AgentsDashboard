<#
.SYNOPSIS
    Detects the COM port of a USB device based on its Vendor ID (VID) and Product ID (PID).
#>
[CmdletBinding()]
param (
    [string]$VID = '303A',
    [string]$PortID = '1001'
)

$hardwareIdPattern = "VID_$VID&PID_$PortID"
Write-Verbose "Searching for devices matching: $hardwareIdPattern"

# Get-CimInstance is the standard in PowerShell 7 (replacing Get-WmiObject)
$devices = Get-CimInstance -ClassName Win32_PnPEntity -Property Name, Caption, PNPDeviceID | 
    Where-Object { $_.PNPDeviceID -match $hardwareIdPattern }

if (-not $devices) {
    Write-Warning "No device found with VID:$VID and PID:$PortID."
    return
}

$foundPorts = foreach ($device in $devices) {
    # Windows typically appends the COM port in parentheses, e.g., "USB Serial Device (COM3)"
    if ($device.Caption -match '\((COM\d+)\)') {
        [PSCustomObject]@{
            Port        = $Matches[1]
            Description = $device.Caption
            DeviceID    = $device.PNPDeviceID
        }
    } else {
        Write-Warning "Device matched, but no COM port was found in its description: $($device.Caption)"
    }
}

# Output the results
$foundPorts
