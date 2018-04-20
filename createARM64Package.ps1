# Update these variables with the paths to the ARM64 appx and pfx used to sign the app.
param (
    [string]$appxPath = "ARM64\Release\DistroLauncher-Appx\DistroLauncher-Appx_1.0.0.0_ARM64.appx",
    [string]$pfxFile = "DistroLauncher-Appx\DistroLauncher-Appx_TemporaryKey.pfx"
)

# Modify the appxmanifest to replace arm64 processor architecture with arm to work around Microsoft Store ingestion issues.
$tempArchive = ".\archive.zip"
$tempFolder = ".\extracted"
Copy-Item $appxPath -Destination $tempArchive
Expand-Archive $tempArchive -DestinationPath $tempFolder -Force
(Get-Content $tempFolder\AppxManifest.xml).replace('ProcessorArchitecture="arm64"', 'ProcessorArchitecture="arm"') | Set-Content $tempFolder\AppxManifest.xml

# Create and sign the appx.
makeappx.exe pack /o /m $tempFolder\AppxManifest.xml /f "DistroLauncher-Appx\ARM64\Release\filemap.map.txt" /p $appxPath
signtool.exe sign /v /f $pfxFile /fd SHA256 $appxPath

# Remove intermediate files.
Remove-Item $tempArchive
Remove-Item $tempFolder -Force -Recurse
