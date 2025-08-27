
#=======================获取当前CMakeLists.txt所在目录的名称=======================
function(get_current_directory_name OUTPUT_VAR)
    get_filename_component(${OUTPUT_VAR} "${CMAKE_CURRENT_LIST_DIR}" NAME)
    set(${OUTPUT_VAR} "${${OUTPUT_VAR}}" PARENT_SCOPE)
endfunction()


#=========================== 获取当前目录下的所有子目录名称（非递归） ===========================
function(get_current_subdirectories result)
    # 查找当前目录下的所有条目
    file(GLOB entries RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
    set(subdirs "")
    
    # 过滤出目录条目
    foreach(entry ${entries})
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${entry})
            list(APPEND subdirs ${entry})
        endif()
    endforeach()
    
    # 将结果存入输出变量
    set(${result} "${subdirs}" PARENT_SCOPE)
endfunction()


#================== 递归查找所有CPP的源文件(*.cpp)和头文件(*.hpp *.h)===================
function(recursive_collect_files source_files_var header_files_var)
    # 递归查找所有.cpp源文件
    file(GLOB_RECURSE SOURCE_FILES_TEMP
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "*.cpp"
    )
    
    # 递归查找所有.h和.hpp头文件
    file(GLOB_RECURSE HEADER_FILES_TEMP
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "*.h"
        "*.hpp"
    )
    
    # 将结果通过参数导出到父作用域
    set(${source_files_var} "${SOURCE_FILES_TEMP}" PARENT_SCOPE)
    set(${header_files_var} "${HEADER_FILES_TEMP}" PARENT_SCOPE)
endfunction()