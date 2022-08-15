cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_BUILD_TYPE "Debug")


# 使用宏进行配置 config.h
set(APP_NAME "图片屏保程序")
configure_file(cmake/config.h.in config.h @ONLY)