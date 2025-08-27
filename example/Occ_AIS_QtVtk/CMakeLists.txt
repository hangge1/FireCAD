

get_current_directory_name(CURRENT_PROJECT_NAME)
message("===========Current directory name: ${CURRENT_PROJECT_NAME}===========")

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

if(MSVC)  
    source_group("Rc Files" FILES ${RC_FILES})
    source_group(TREE ${SRC_DIR} FILES ${SRC_FILES} ${HEADER_FILES} ${HEADER_FILES} ${UI_FILES})
endif()

qt_add_executable(${CURRENT_PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${CURRENT_PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${CURRENT_PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)



target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${SRC_DIR})

#process dep OCCT
target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})
foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()


#process dep VTK
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS ${CURRENT_PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)

# set debugger environment
set_property(TARGET ${CURRENT_PROJECT_NAME} 
PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:DEBUG>:${OpenCASCADE_BINARY_DIR}d>$<$<NOT:$<CONFIG:DEBUG>>:${OpenCASCADE_BINARY_DIR}>;${VTK_PREFIX_PATH}/bin;${QT_DIR}/../../../bin;%PATH%")

