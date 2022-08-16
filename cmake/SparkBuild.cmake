cmake_minimum_required(VERSION 3.5.1)

set(QRCS resources/sources.qrc)

# 1. 核心配置库，拥有操作配置文件以及提供读取图片文件的功能
spark_add_libraries_path(ScreenSaverConfig
    src/ScreenSaverConfig)
target_link_qt5(ScreenSaverConfig)

# 2. 主要屏保库，提供主要的预览图片功能，依赖 ScreenSaverConfig 提供的图片读取
spark_add_libraries_path(ScreenSaverImage
    src/ScreenSaverImage)
target_link_ScreenSaverConfig(ScreenSaverImage)

# 3. 主屏保程序，提供主要的屏保状态执行效果，依赖 ScreenSaverImage 提供的预览图片功能
spark_add_executable_path(${PROJECT_NAME} 
    src ${QRCS})
target_link_ScreenSaverImage(${PROJECT_NAME})

# 4. 配置面板程序，提供配置屏保的面板，以及预览屏保的功能
    # 依赖 ScreenSaverImage 提供的预览图片功能
    # 间接依赖 ScreenSaverConfig 对配置文件的处理功能
spark_add_executable_path(picture-screensaver-config-panel 
    tools/ConfigPanel
    ${QRCS})
target_link_ScreenSaverImage(picture-screensaver-config-panel)
