#!/bin/bash

# 每次都设置默认屏保为 'picture-screensaver'
dbus-send --session --print-reply=literal       \
    --dest=com.deepin.ScreenSaver               \
        /com/deepin/ScreenSaver                 \
            org.freedesktop.DBus.Properties.Set \
            'string:com.deepin.ScreenSaver'     \
            'string:currentScreenSaver'         \
            'variant:string:picture-screensaver'\

# 设置使用电池时
dbus-send --session --print-reply=literal       \
    --dest=com.deepin.ScreenSaver               \
        /com/deepin/ScreenSaver                 \
            org.freedesktop.DBus.Properties.Set \
            'string:com.deepin.ScreenSaver'     \
            'string:batteryScreenSaverTimeout'  \
            'variant:int32:60'                  \


# 设置使用电源时
dbus-send --session --print-reply=literal       \
    --dest=com.deepin.ScreenSaver               \
        /com/deepin/ScreenSaver                 \
            org.freedesktop.DBus.Properties.Set \
            'string:com.deepin.ScreenSaver'     \
            'string:linePowerScreenSaverTimeout'\
            'variant:int32:60'                  \


# 设置使用唤醒时进入锁屏状态
# dbus-send --session --print-reply=literal       \
#     --dest=com.deepin.ScreenSaver               \
#         /com/deepin/ScreenSaver                 \
#             org.freedesktop.DBus.Properties.Set \
#             'string:com.deepin.ScreenSaver'     \
#             'string:lockScreenAtAwake'          \
#             'variant:boolean:true'              \


# 设置锁屏延时
# dbus-send --session --print-reply=literal       \
#     --dest=com.deepin.ScreenSaver               \
#         /com/deepin/ScreenSaver                 \
#             org.freedesktop.DBus.Properties.Set \
#             'string:com.deepin.ScreenSaver'     \
#             'string:lockScreenDelay'            \
#             'variant:int32:1'                   \


# 使用电源:
# 设置关闭显示器为从不
# gsettings set com.deepin.dde.power line-power-screen-black-delay 0   
# 使用电池:
# gsettings set com.deepin.dde.power battery-screen-black-delay 900