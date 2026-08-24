$port = [System.IO.Ports.SerialPort]::new("COM3", 115200, "None", 8, "One")
$port.ReadTimeout = 100
$port.NewLine = "`r`n"

try {
    $port.Open()
    $port.DiscardInBuffer()
    $port.Write("AT`r")
    Start-Sleep -Milliseconds 50

    $response = New-Object System.Text.StringBuilder

    while ($true) {
        try {
            $line = $port.ReadLine()
            [void]$response.AppendLine($line)
        }
        catch [System.TimeoutException] {
            break
        }
    }

    $text = $response.ToString().Trim()
    if ([string]::IsNullOrWhiteSpace($text)) {
        "No response received within 1s."
    }
    else {
        $text
    }
}
finally {
    if ($port.IsOpen) { $port.Close() }
    $port.Dispose()
}
