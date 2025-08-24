cmake_minimum_required(VERSION 3.16)

project("FireCAD" 
    VERSION 0.1.0
    LANGUAGES CXX C
    DESCRIPTION "This is an example for Framework FireCAD which is a great studying material"
)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

include(cmake/tool.cmake)


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

# ==================== Find VTK ====================
set(VTK_CMAKE_DIR "" CACHE PATH "Path to VTK root directory")
if(NOT VTK_CMAKE_DIR)
    set(VTK_CMAKE_DIR $ENV{VTK_CMAKE_DIR})
endif()
if(NOT VTK_CMAKE_DIR)
    message(FATAL_ERROR "VTK_CMAKE_DIR is not set. Please set VTK_CMAKE_DIR cache variable or environment variable.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${VTK_CMAKE_DIR}")

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

# ====================End Find VTK ====================

add_subdirectory(Example)