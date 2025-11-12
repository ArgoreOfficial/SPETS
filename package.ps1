& "xmake" f -c -y -m "release"
& "xmake" build -y 
& "xmake" install -o package

if( $LASTEXITCODE -lt 0 )
{
    write-host "Press any key to continue..."
    [void][System.Console]::ReadKey($true)
}
