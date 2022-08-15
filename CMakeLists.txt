
cmake_minimum_required(VERSION 3.5.1)

project(picture-screensaver VERSION 0.0.1)

include(cmake/SparkEnvConfig.cmake)         # 设置一些有关QT构建的开关
include(cmake/SparkFindQt5Config.cmake)     # 提供了 target_link_qt5 用于目标链接 qt5 的库
include(cmake/SparkFindDtkConfig.cmake)     # 提供了 target_link_dtk 用于目标链接 dtk 的库
include(cmake/SparkMacrosConfig.cmake)      # 声明了一些 spark_ 开头的 macro 宏
