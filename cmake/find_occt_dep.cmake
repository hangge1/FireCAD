
# ==================== Find OpenCASCADE ====================
set(OCC_CMAKE_DIR "" CACHE PATH "Path to OpenCASCADE cmake directory")
if(NOT OCC_CMAKE_DIR)
    set(OCC_CMAKE_DIR $ENV{OCC_CMAKE_DIR})
endif()
if(NOT OCC_CMAKE_DIR)
    message(FATAL_ERROR "OCC_CMAKE_DIR is not set. Please set OCC_CMAKE_DIR cache variable or environment variable.")
else()
    message("========Using: OCC_CMAKE_DIR: ${OCC_CMAKE_DIR}")
endif()



list(APPEND CMAKE_PREFIX_PATH "${OCC_CMAKE_DIR}")
find_package(OpenCASCADE)
if (NOT OpenCASCADE_FOUND)
    message(FATAL_ERROR "OpenCASCADE not found. Please set OCC_CMAKE_DIR cache variable or environment variable.")
else()
    message("========Using: OpenCASCADE_DIR: ${OpenCASCADE_DIR}")
endif()

# ==================== End Find OpenCASCADE ====================