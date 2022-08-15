cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INSTALL_PREFIX    "/usr")
set(CMAKE_INSTALL_ROOTDIR   "../")
set(CMAKE_INSTALL_SCREENSAVERDIR "lib/deepin-screensaver/modules/")

# 屏保程序本身
install(TARGETS 
    ${PROJECT_NAME}

    DESTINATION ${CMAKE_INSTALL_SCREENSAVERDIR}
)

install(DIRECTORY 
    rootfs/usr

    USE_SOURCE_PERMISSIONS
    DESTINATION ${CMAKE_INSTALL_ROOTDIR}
)

install(TARGETS
    picture-screensaver-config-panel
    
    DESTINATION "share/${PROJECT_NAME}"
)

