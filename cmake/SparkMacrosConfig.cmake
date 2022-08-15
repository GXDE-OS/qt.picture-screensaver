cmake_minimum_required(VERSION 3.5.1)

# 定义一些 macro 用于自动生成构建结构

# spark_add_libraries <lib_name> [files]...
# 构建一个库，基于指定的源文件
    # 并根据库名生成 target_link_<lib_name> 函数
macro(spark_add_libraries _lib_name)
    message("================ ${_lib_name} Library ================")
    add_library(${_lib_name} ${ARGN})
    
    set(SRCS ${ARGN})
    foreach(item IN LISTS SRCS)
        message(" -> ${item}")
    endforeach(item IN LISTS SRCS)
    
    function(target_link_${_lib_name} TARGET)
        message("${_lib_name}")
        target_link_libraries(${TARGET} ${_lib_name})
    endfunction(target_link_${_lib_name} TARGET)

endmacro(spark_add_libraries _lib_name)

# spark_add_libraries_path <lib_name> <lib_path>
# 构建一个库，基于指定的路径
    # 并根据库名生成 target_link_<lib_name> 函数
        # 函数内增加以 <lib_path> 头文件搜索路径
macro(spark_add_libraries_path _lib_name _lib_path)
    aux_source_directory(${_lib_path} ${_lib_name}_SOURCES)

    message("================ spark_add_libraries_path: ${_lib_name} ================")

    add_library(${_lib_name} ${${_lib_name}_SOURCES})
    foreach(item IN LISTS ${_lib_name}_SOURCES)
        message(" -> ${item}")
    endforeach(item IN LISTS ${_lib_name}_SOURCES)
    
    function(target_link_${_lib_name} TARGET)
        # message("target_link_${_lib_name}")
        message(" -> (include): ${_lib_path}")
        target_include_directories(${TARGET} PUBLIC "${_lib_path}")
        target_link_libraries(${TARGET} ${_lib_name})
    endfunction(target_link_${_lib_name} TARGET)

endmacro(spark_add_libraries_path _lib_name _lib_path)

# spark_add_executable <exec_name> [files]...
# 构建一个可执行文件，基于指定的源文件
    # Qt编译时源文件包括很多类型，需要指定 *.h/*.cpp/*.qrc/*.qm/... 等
macro(spark_add_executable _exec_name)

    message("================ ${_exec_name} Executable ================")
    add_executable(${_exec_name} ${ARGN})

endmacro(spark_add_executable _exec_name)

macro(spark_add_executable_path _exec_name _exec_path)
    aux_source_directory(${_exec_path} ${_exec_name}_SOURCES)

    message("================ ${_exec_name} Executable ================")
    
    add_executable(${_exec_name} ${${_exec_name}_SOURCES} ${ARGN})
    foreach(item IN LISTS ${_exec_name}_SOURCES)
        message(" -> ${item}")
    endforeach(item IN LISTS ${_exec_name}_SOURCES)
    
    # function(target_link_${_exec_name} TARGET)
    #     message("target_link_${_lib_name}")
    message(" -> (include): ${_exec_path}")
    target_include_directories(${_exec_name} PUBLIC "${_exec_path}")
        # target_link_libraries(${TARGET} ${_lib_name})
    # endfunction(target_link_${_exec_name} TARGET)
    # target_link_${_exec_name}(${_exec_name})

endmacro(spark_add_executable_path _exec_name _exec_path)

# spark_find_library
# 搜索一个库，基于指定的库名，调用 pkg-config 搜索库
    # 并根据库名生成一个 target_link_<prefix> 函数
macro(spark_find_library _prefix)
    find_package(PkgConfig REQUIRED)
    
    # libnotify
    pkg_check_modules(${_prefix} ${ARGN})
    function(target_link_${_prefix} TARGET)
        target_include_directories(${TARGET} PUBLIC 
            ${${_prefix}_INCLUDE_DIRS})
        target_link_libraries(${TARGET} 
            ${${_prefix}_LIBRARIES})
    endfunction(target_link_${_prefix} TARGET)
    
endmacro(spark_find_library _prefix)

