

get_current_directory_name(CURRENT_PROJECT_NAME)
message("===========Current directory name: ${CURRENT_PROJECT_NAME}===========")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE QRC_FILES "*.qrc")
file(GLOB_RECURSE UI_FILES "${SRC_DIR}/*.ui")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "main.cpp")
file(GLOB_RECURSE HEADER_FILES "${SRC_DIR}/*.h" "${SRC_DIR}/*.hpp")

set(PROJECT_SOURCES
    ${QRC_FILES}
    ${UI_FILES}
    ${SRC_FILES}
    ${HEADER_FILES}
)

if(MSVC)  
    source_group("Qrc Files" FILES ${QRC_FILES})
    # source_group("Ui Files" FILES ${UI_FILES})
    # source_group("Src Files" FILES ${SRC_FILES})
    # source_group("Header Files" FILES ${HEADER_FILES})
    source_group(TREE ${SRC_DIR} FILES ${SRC_FILES} ${HEADER_FILES} ${UI_FILES})
endif()

set(CMAKE_AUTORCC ON)
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

if(MSVC) 
  target_compile_options(${CURRENT_PROJECT_NAME} PRIVATE /utf-8)
endif()



target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${SRC_DIR})

#process dep OCCT
target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})
foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
  target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

# set debugger environment
set_property(TARGET ${CURRENT_PROJECT_NAME} 
PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:DEBUG>:${OpenCASCADE_BINARY_DIR}d>$<$<NOT:$<CONFIG:DEBUG>>:${OpenCASCADE_BINARY_DIR}>;${QT_DIR}/../../../bin;%PATH%")

