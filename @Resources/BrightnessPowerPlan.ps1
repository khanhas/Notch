function GetBrightness {
    return (Get-WmiObject WmiMonitorBrightness -Namespace root/WMI).CurrentBrightness
}

$brightnessMethod
function SetBrightness() {
    param(
        $value,
        $isRelative = $false
    )
    if ($null -eq $brightnessMethod) {
        $Global:brightnessMethod = Get-WmiObject WmiMonitorBrightNessMethods -Namespace root/WMI
    }

    if ($isRelative) {
        $value = (GetBrightness) + $value
    }
    $brightnessMethod.WmiSetBrightness(0, $value)
}

function TurnOffMonitor {
    Add-Type 'public static class Win32{
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern int SendMessage(int hWnd, int hMsg, int wParam, int lParam);
    }'

    [Win32]::SendMessage(0xffff, 0x0112, 0xf170, 0x0002)
}

function SetActivePlan($guid) {
    powercfg /setactive $guid
    SetPlanMeter
}

function SetPlanMeter {
    $index = 0
    (powercfg /l) | Where-Object {$_.Contains('GUID')} | ForEach-Object {
        $index++
        $_ -match "\((.*)\)"
        $name = $Matches[1]
        $isActive = $_.Contains("*")
        $guid = $_.Split()[3]

        $RmAPI.Bang("!SetOption Powerplan$index Text `"$name`"")
        $RmAPI.Bang("!ShowMeter Powerplan$index")
        if ($isActive) {
            $RmAPI.Bang("!SetVariable Active $index")
            $RmAPI.Bang("!SetOption Powerplan$index LeftMouseUpAction `"`"")
        } else {
            $RmAPI.Bang("!SetOption Powerplan$index LeftMouseUpAction `"`"`"[!CommandMeasure PSRM `"SetActivePlan $guid`"][!Update]`"`"`"")
        }
    }

    $RmAPI.Bang("!SetVariable Total $index")
}

SetPlanMeter