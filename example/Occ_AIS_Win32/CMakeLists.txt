
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


get_current_directory_name(CURRENT_PROJECT_NAME)
message("===========Current directory name: ${CURRENT_PROJECT_NAME}===========")

recursive_collect_files(SOURCE_FILES HEADER_FILES)
add_executable (${CURRENT_PROJECT_NAME}
  ${SOURCE_FILES} 
  ${HEADER_FILES}
)

if(WIN32)
  set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
      WIN32_EXECUTABLE TRUE
  )

  if (MSVC)
    target_compile_options(${CURRENT_PROJECT_NAME} PRIVATE "/utf-8")
  endif()
endif()



target_include_directories (${CURRENT_PROJECT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})


foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(${CURRENT_PROJECT_NAME} debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(${CURRENT_PROJECT_NAME} optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

target_link_libraries(${CURRENT_PROJECT_NAME} ${VTK_LIBRARIES})

set_property(TARGET ${CURRENT_PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:DEBUG>:${OpenCASCADE_BINARY_DIR}d>$<$<NOT:$<CONFIG:DEBUG>>:${OpenCASCADE_BINARY_DIR}>;${VTK_PREFIX_PATH}/bin;%PATH%")

vtk_module_autoinit(
  TARGETS ${CURRENT_PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)