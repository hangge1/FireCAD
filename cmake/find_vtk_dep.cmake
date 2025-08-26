
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