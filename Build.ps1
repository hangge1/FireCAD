param(
    [int]$RemoveBuildDir = 0

)

if ($RemoveBuildDir ) {
    if (Test-Path -Path "./build") {
        Remove-Item -Path "./build" -Recurse -Force -ErrorAction Stop
        Write-Host "build dir has deleted"
    }
}

$OCC_CMAKE_DIR = if ($env:OCC_CMAKE_DIR) { $env:OCC_CMAKE_DIR } else { "D:/codeProject/OCCT-7_9_1/OCCT-install/cmake" }
$QT_CMAKE_DIR = if ($env:QT_CMAKE_DIR) { $env:QT_CMAKE_DIR } else { "D:/software/Qt/6.9.1/msvc2022_64/lib/cmake" }

cmake -S . -B build -DOCC_CMAKE_DIR="$OCC_CMAKE_DIR" -DQT_CMAKE_DIR="$QT_CMAKE_DIR"
cmake --build build --config Debug