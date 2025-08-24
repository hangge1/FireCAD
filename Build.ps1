param(
    [int]$RemoveBuildDir = 0

)

if ($RemoveBuildDir ) {
    if (Test-Path -Path "./build") {
        Remove-Item -Path "./build" -Recurse -Force -ErrorAction Stop
        Write-Host "build dir has deleted"
    }
}

# you can edit these hard code to your own path
$user_occ_dir = "D:/codeProject/OCCT-7_9_1/OCCT-install/cmake"
$user_vtk_dir = "D:/codeProject/VTK-9.5.0-Install/lib/cmake/vtk-9.5"
$user_qt_dir = "D:/software/Qt/6.9.1/msvc2022_64/lib/cmake"


$OCC_CMAKE_DIR = if ($env:OCC_CMAKE_DIR) { $env:OCC_CMAKE_DIR } else { "$user_occ_dir" }
$QT_CMAKE_DIR = if ($env:QT_CMAKE_DIR) { $env:QT_CMAKE_DIR } else { "$user_qt_dir" }
$VTK_CMAKE_DIR = if ($env:VTK_CMAKE_DIR) { $env:VTK_CMAKE_DIR } else { "$user_vtk_dir" }


cmake -S . -B build -DOCC_CMAKE_DIR="$OCC_CMAKE_DIR" -DQT_CMAKE_DIR="$QT_CMAKE_DIR" -DVTK_CMAKE_DIR="$VTK_CMAKE_DIR"

cmake --build build --config Debug