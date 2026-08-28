param (
    [string]$VID = '303A',
    [string]$ProductID = '1001'
)

Get-CimInstance -ClassName Win32_PnPEntity -Property Caption, PNPDeviceID | 
    Where-Object { $_.PNPDeviceID -match "VID_$VID&PID_$ProductID" } | 
    ForEach-Object {
        if ($_.Caption -match '\((COM\d+)\)') {
            $Matches[1]
        }
    }