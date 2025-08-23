
function(get_current_directory_name OUTPUT_VAR)
    get_filename_component(${OUTPUT_VAR} "${CMAKE_CURRENT_LIST_DIR}" NAME)
    set(${OUTPUT_VAR} "${${OUTPUT_VAR}}" PARENT_SCOPE)
endfunction()

