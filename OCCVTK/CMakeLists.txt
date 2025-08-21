cmake_minimum_required (VERSION 3.15.0 FATAL_ERROR)

project (OCC_PROJECT LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)


list(APPEND CMAKE_PREFIX_PATH "D:\\codeProject\\OCCT-7_9_1\\OCCT-install\\cmake")


find_package(OpenCASCADE)
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
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "CylinderExample: Unable to find the VTK build folder.")
endif()


add_executable (OCC_PROJECT
  OcctAisHello.cpp
)

target_include_directories (OCC_PROJECT PRIVATE ${OpenCASCADE_INCLUDE_DIR})


foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(OCC_PROJECT debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(OCC_PROJECT optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

target_link_libraries(OCC_PROJECT ${VTK_LIBRARIES})

set_property(TARGET OCC_PROJECT PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:DEBUG>:${OpenCASCADE_BINARY_DIR}d>$<$<NOT:$<CONFIG:DEBUG>>:${OpenCASCADE_BINARY_DIR}>;%PATH%")

vtk_module_autoinit(
  TARGETS OCC_PROJECT
  MODULES ${VTK_LIBRARIES}
)