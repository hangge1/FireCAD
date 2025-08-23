cmake_minimum_required(VERSION 3.16)
project(QtVtkOcct 
LANGUAGES CXX C
DESCRIPTION "This is an example cmake project for integrate OOCT + QT + VTK"
)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "D:\\codeProject\\OCCT-7_9_1\\OCCT-install\\cmake")
#list(APPEND CMAKE_PREFIX_PATH "D:\\codeProject\\VTK-9.5.0-Install\\lib\\cmake\\vtk-9.5")

# occt
find_package(OpenCASCADE)


# vtk
find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  GUISupportQt
)
if (NOT VTK_FOUND)
  message(FATAL_ERROR "Unable to find the VTK build folder.")
endif()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    qtvtkocct.ui
    qtvtkocct.h
    qtvtkocct.cpp
    QtVtkOcct.rc
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

#process dep OCCT
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})
foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} PRIVATE debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(${PROJECT_NAME} PRIVATE optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:DEBUG>:${OpenCASCADE_BINARY_DIR}d>$<$<NOT:$<CONFIG:DEBUG>>:${OpenCASCADE_BINARY_DIR}>;%PATH%")

#process dep VTK
target_link_libraries(${PROJECT_NAME} PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS ${PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)