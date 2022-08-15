cmake_minimum_required(VERSION 3.5.1)

find_package(Qt5 COMPONENTS Core Gui Widgets Network Concurrent WebEngineWidgets)

function(target_link_qt5 NAME)
    target_link_libraries(${NAME} 
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
        Qt5::Gui)
endfunction(target_link_qt5 NAME)

function(target_link_qt5_concurrent)
    target_link_libraries(${NAME} 
        Qt5::Concurrent)
endfunction(target_link_qt5_concurrent)
    
function(target_link_qt5_webenginewidgets)
    target_link_libraries(${NAME} 
        Qt5::WebEngineWidgets)
endfunction(target_link_qt5_webenginewidgets)

