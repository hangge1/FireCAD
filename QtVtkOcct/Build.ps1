if (Test-Path -Path "./build") {
    Remove-Item -Path "./build" -Recurse -Force -ErrorAction Stop
    Write-Host "build dir has deleted"
}

cmake -S . -B build -DOCC_CMAKE_DIR="D:/codeProject/OCCT-7_9_1/OCCT-install/cmake" -DQT_CMAKE_DIR="D:/software/Qt/6.9.1/msvc2022_64/lib/cmake"
cmake --build build --config Debug