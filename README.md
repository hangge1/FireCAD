# FireCAD
This is a project for recording my studing experience of OCCT + VTK + QT



# Dependencies:

1、OCCT  (7.9.1)

2、VTK (9.5.0)

3、QT6 (6.9.1)

4、CMake  > 3.16



# Build Dependencies: 

1.  use CMake GUI 
2.  build dependency 【OCCT + VTK】
3.  install dependency 【OCCT + VTK】

QT：use prebuild binary package， and add the bin path To PATH



# Build

- Set Dependency Library Find Path
  - method 1:  edit the Build.ps1
    - search this sentence:  \# you can edit these hard code to your own path
    - edit 3 variables:  user_occ_dir、user_vtk_dir、user_qt_dir
  - method2: set ENV variables  【don't forget reboot PC】
    - OCC_CMAKE_DIR
    - QT_CMAKE_DIR
    - VTK_CMAKE_DIR



run this power shell batch:  `./Build.ps1`

**Note:**  these path is point to the :   FindXXX.cmake  dir path  for search Library





# Run
cd build
open .sln  with  Visual Stdio 2022
run QtVtkOcct Project





# Result

![image-20250824153952170](./assets/FireCAD.png)
