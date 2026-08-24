[CmdletBinding()]
param(
    [Parameter(Mandatory = $true, Position = 0)]
    [ValidateNotNullOrEmpty()]
    [string]$IDEName,

    [Parameter(Mandatory = $true, Position = 1)]
    [ValidateNotNullOrEmpty()]
    [string]$Working,

    [Parameter(Position = 2)]
    [ValidateNotNullOrEmpty()]
    [string]$PortDevice = "COM3"
)

$port = [System.IO.Ports.SerialPort]::new($PortDevice, 115200, "None", 8, "One")
$port.ReadTimeout = 1000
$port.WriteTimeout = 100

try {
    $port.Open()
    $port.DiscardInBuffer()

    $command = "AT+PlaceAgentStatus=$IDEName,$Working`r"
    $port.Write($command)

    Start-Sleep -Milliseconds 100

    if ($port.BytesToRead -gt 0) {
        $response = $port.ReadExisting().Trim()
        if (-not [string]::IsNullOrWhiteSpace($response)) {
            $response
        }
    }
}
finally {
    if ($port.IsOpen) { $port.Close() }
    $port.Dispose()
}
