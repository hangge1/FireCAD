cmake_minimum_required(VERSION 3.16)

project("FireCAD" 
    VERSION 0.1.0
    LANGUAGES CXX C
    DESCRIPTION "This is an example for Framework FireCAD which is a great studying material"
)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

include(cmake/tool.cmake)
include(cmake/find_occt_dep.cmake)
include(cmake/find_qt_dep.cmake)
include(cmake/find_vtk_dep.cmake)

add_subdirectory(Example)