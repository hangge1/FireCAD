# ==================== Find Qt ====================
set(QT_CMAKE_DIR "" CACHE PATH "Path to QT root directory")
if(NOT QT_CMAKE_DIR)
    set(QT_CMAKE_DIR $ENV{QT_CMAKE_DIR})
endif()
if(NOT QT_CMAKE_DIR)
    message(FATAL_ERROR "QT_CMAKE_DIR is not set. Please set QT_CMAKE_DIR cache variable or environment variable.")
else()
    message("========Using: QT_CMAKE_DIR: ${QT_CMAKE_DIR}")
endif()

list(APPEND CMAKE_PREFIX_PATH "${QT_CMAKE_DIR}")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core) #find Qt Version is 6 or 5, 6 is higher priority
if (NOT QT_VERSION_MAJOR)
    message(FATAL_ERROR " QT_VERSION_MAJOR not found. Please set QT_CMAKE_DIR cache variable or environment variable.")
else()
    message("========Using: Qt Version: ${QT_VERSION_MAJOR}")
endif()

find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
if (NOT Qt${QT_VERSION_MAJOR}_FOUND)
    message(FATAL_ERROR " Qt${QT_VERSION_MAJOR} not found. Please set QT_CMAKE_DIR cache variable or environment variable.")
endif()

include(cmake/qt.cmake)
qt_standard_project_setup()

# ==================== End Find Qt ====================