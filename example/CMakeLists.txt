

get_current_subdirectories(subdirs)
message("================Find Examples: ${subdirs}")

foreach(DirName ${subdirs})
    add_subdirectory(${DirName})
endforeach()

