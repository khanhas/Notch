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
        $plan = $_.Split()
        $guid = $plan[3]
        $name = $plan[5].SubString(1, $plan[5].Length - 2)
        $RmAPI.Bang("!SetOption Powerplan$index Text `"$name`"")
        $RmAPI.Bang("!ShowMeter Powerplan$index")
        if ($plan.Length -eq 6) {
            $RmAPI.Bang("!SetOption Powerplan$index LeftMouseUpAction `"`"`"[!CommandMeasure PSRM `"SetActivePlan $guid`"][!Update]`"`"`"")
        } else {
            $RmAPI.Bang("!SetVariable Active $index")
        }
    }

    $RmAPI.Bang("!SetVariable Total $index")
}

SetPlanMeter