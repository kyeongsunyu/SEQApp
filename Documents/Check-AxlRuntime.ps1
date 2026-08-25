<#
    AXL 런타임 진단 스크립트

    32/64비트가 섞여 0xC000007B(STATUS_INVALID_IMAGE_FORMAT)로 죽는 원인을 찾는다.
    Windows 의 DLL 검색 순서를 그대로 따라가며, 각 위치의 AXL 관련 DLL 아키텍처를
    보여주고 "실제로 로드될 파일"을 판정한다.

    사용법:
        powershell -ExecutionPolicy Bypass -File Check-AxlRuntime.ps1
        powershell -ExecutionPolicy Bypass -File Check-AxlRuntime.ps1 -ExeDir D:\OTHER
#>
param(
    [string]$ExeDir  = 'C:\WORK',
    [string]$ExeName = 'SEQApp.exe'
)

function Get-PeInfo([string]$Path) {
    $fs = $null
    try {
        $fs = [IO.File]::Open($Path, [IO.FileMode]::Open, [IO.FileAccess]::Read, [IO.FileShare]::ReadWrite)
        $br = New-Object IO.BinaryReader($fs)
        $fs.Position = 0x3C
        $peOff = $br.ReadInt32()
        $fs.Position = $peOff + 4
        $machine = $br.ReadUInt16()
        $fs.Position = $peOff + 8
        $stamp = $br.ReadUInt32()
        $arch = switch ($machine) { 0x14C { 'x86' } 0x8664 { 'x64' } default { '0x{0:X}' -f $machine } }
        $link = try { [DateTimeOffset]::FromUnixTimeSeconds($stamp).UtcDateTime.ToString('yyyy-MM-dd') } catch { '?' }
        [pscustomobject]@{ Arch = $arch; Link = $link; Size = (Get-Item $Path).Length }
    } catch {
        [pscustomobject]@{ Arch = '읽기실패'; Link = ''; Size = 0 }
    } finally {
        if ($fs) { $fs.Dispose() }
    }
}

# Windows DLL 검색 순서 (안전 검색 모드 기준)
$searchDirs = @(
    $ExeDir                          # 1. 실행 파일 폴더 - 최우선
    "$env:SystemRoot\System32"       # 2. 시스템 폴더 (32비트 프로세스는 SysWOW64 로 리다이렉트)
    "$env:SystemRoot\SysWOW64"
    "$env:SystemRoot\System"         # 3. 16비트 시절 폴더 - AXL 설치본이 여기 심는다
    "$env:SystemRoot"                # 4. Windows 폴더
) + (($env:PATH -split ';') | Where-Object { $_ })   # 5. PATH
$searchDirs = $searchDirs | Where-Object { $_ } | Select-Object -Unique

$targets = 'AXL.dll', 'EzBasicAxl.dll', 'WIBUCM32.dll', 'WIBUCM64.dll'

# 실행 파일 아키텍처
$exePath = Join-Path $ExeDir $ExeName
if (Test-Path $exePath) {
    $exe = Get-PeInfo $exePath
    Write-Host ""
    Write-Host ("실행 파일 : {0}  [{1}]  {2:N0} bytes" -f $exePath, $exe.Arch, $exe.Size) -ForegroundColor Cyan
} else {
    $exe = $null
    Write-Host ""
    Write-Host "실행 파일을 찾을 수 없습니다: $exePath" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "=== 발견된 AXL 관련 DLL (검색 순서대로) ===" -ForegroundColor Cyan

$found = @{}
foreach ($dir in $searchDirs) {
    foreach ($name in $targets) {
        $p = Join-Path $dir $name
        if (Test-Path $p -PathType Leaf) {
            $info = Get-PeInfo $p
            if (-not $found.ContainsKey($name)) { $found[$name] = $p }   # 첫 히트 = 실제 로드될 파일
            $mark = ''
            if ($exe -and $info.Arch -ne $exe.Arch -and $info.Arch -match '^x(86|64)$') { $mark = '  <== 비트 불일치' }
            $line = '{0,-14} {1,-5} {2,12:N0}  {3}  {4}{5}' -f $name, $info.Arch, $info.Size, $info.Link, $p, $mark
            if ($mark) { Write-Host $line -ForegroundColor Red } else { Write-Host $line }
        }
    }
}

Write-Host ""
Write-Host "=== 실제로 로드될 파일 (검색 순서 첫 히트) ===" -ForegroundColor Cyan
foreach ($name in $targets) {
    if ($found.ContainsKey($name)) {
        $info = Get-PeInfo $found[$name]
        $verdict = if (-not $exe) { '' }
                   elseif ($info.Arch -eq $exe.Arch) { 'OK' }
                   else { "불일치 - exe 는 $($exe.Arch)" }
        $color = if ($verdict -eq 'OK' -or $verdict -eq '') { 'Green' } else { 'Red' }
        Write-Host ("{0,-14} {1,-5} {2}  [{3}]" -f $name, $info.Arch, $found[$name], $verdict) -ForegroundColor $color
    } else {
        Write-Host ("{0,-14} 검색 경로에서 찾지 못함" -f $name) -ForegroundColor DarkGray
    }
}

# EzBasicAxl.dll 은 VC++ 2005(MSVCR80/MFC80) 를 요구한다 - 없으면 0xC0150004 로 죽는다
Write-Host ""
Write-Host "=== VC++ 2005 재배포 (EzBasicAxl.dll 의 MSVCR80 / MFC80 의존) ===" -ForegroundColor Cyan
foreach ($arch in 'x86', 'amd64') {
    $hit = Get-ChildItem "$env:SystemRoot\WinSxS" -Directory -Filter "$($arch)_microsoft.vc80.*" -ErrorAction SilentlyContinue
    if ($hit) {
        Write-Host ("{0,-6} 설치됨 ({1}개 어셈블리)" -f $arch, $hit.Count) -ForegroundColor Green
    } else {
        Write-Host ("{0,-6} 없음 - 해당 비트로 빌드하면 EzBasicAxl.dll 로드가 0xC0150004 로 실패한다" -f $arch) -ForegroundColor Red
    }
}
Write-Host ""
