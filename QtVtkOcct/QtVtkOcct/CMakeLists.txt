cmake_minimum_required(VERSION 3.16)
project(QtVtkOcct 
    LANGUAGES CXX C
    DESCRIPTION "This is an example cmake project for integrate OOCT + QT + VTK"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#list(APPEND CMAKE_PREFIX_PATH "D:/codeProject/OCCT-7_9_1/OCCT-install/cmake")
#list(APPEND CMAKE_PREFIX_PATH "D:/codeProject/VTK-9.5.0-Install/lib/cmake/vtk-9.5")


# ==================== Find OpenCASCADE ====================
set(OCC_CMAKE_DIR "" CACHE PATH "Path to OpenCASCADE cmake directory")
if(NOT OCC_CMAKE_DIR)
    set(OCC_CMAKE_DIR $ENV{OCC_CMAKE_DIR})
endif()
if(NOT OCC_CMAKE_DIR)
    message(FATAL_ERROR "OCC_CMAKE_DIR is not set. Please set OCC_CMAKE_DIR cache variable or environment variable.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${OCC_CMAKE_DIR}")
find_package(OpenCASCADE)
if (NOT OpenCASCADE_FOUND)
    message(FATAL_ERROR "OpenCASCADE not found. Please set OCC_ROOT cache variable or environment variable.")
endif()

# ==================== End Find OpenCASCADE ====================

# ==================== Find Qt ====================
set(QT_CMAKE_DIR "" CACHE PATH "Path to QT root directory")
if(NOT QT_CMAKE_DIR)
    set(QT_CMAKE_DIR $ENV{QT_CMAKE_DIR})
endif()
if(NOT QT_CMAKE_DIR)
    message(FATAL_ERROR "QT_CMAKE_DIR is not set. Please set QT_CMAKE_DIR cache variable or environment variable.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${QT_CMAKE_DIR}")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

if (NOT QT_FOUND)
    message(FATAL_ERROR " Qt not found. Please set QT_ROOT cache variable or environment variable.")

endif()

include(cmake/qt.cmake)
# ==================== End Find Qt ====================


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



set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resource)


file(GLOB_RECURSE RC_FILES "${RES_DIR}/*.rc")
file(GLOB_RECURSE UI_FILES "${SRC_DIR}/*.ui")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "main.cpp")
file(GLOB_RECURSE HEADER_FILES "${SRC_DIR}/*.h" "${SRC_DIR}/*.hpp")

set(PROJECT_SOURCES
    ${RC_FILES}
    ${UI_FILES}
    ${SRC_FILES}
    ${HEADER_FILES}
)

source_group("src" FILES ${SRC_FILES} ${HEADER_FILES} ${HEADER_FILES})
source_group("ui" FILES ${UI_FILES})
source_group("resource" FILES ${RC_FILES})

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

target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})

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


