& "xmake" f -y --vs=2026
& "xmake" project -k vsxmake -y -m "debug, release" -a "x64" ./build

if( $LASTEXITCODE -lt 0 )
{
    write-host "Press any key to continue..."
    [void][System.Console]::ReadKey($true)
}
else {
    Get-ChildItem "$(Get-Item .)\build\vsxmake2026" -Filter *.sln |
    ForEach-Object {
        write-host ($_.BaseName)
        $WshShell = New-Object -COMObject WScript.Shell
        $Shortcut = $WshShell.CreateShortcut("$(Get-Item .)\$($_.BaseName).sln.lnk")
        $Shortcut.TargetPath = "$(Get-Item .)\build\vsxmake2026\$($_.BaseName).sln"
        $Shortcut.Save()
    }
}
