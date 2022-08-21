# qt.picture-screensaver 

> 适用于深度操作系统的动态图片屏保程序

## 屏保演示

* 在配置好屏幕保护设置后，执行 `deepin-screensaver` 即可立即预览屏保效果
    ![](resources/screenshots/screenshot4.png)

## 构建说明

- 执行以下命令进行构建或运行与打包
    ```sh
    $ make         # 将构建 Debug 模式的应用程序，适合在 Debug 模式运行
    $ make run     # 将自动构建 Debug 模式的应用程序，并运行
    $ make package # 将自动构建 Release 模式的应用程序，并打包为 deb
    # 以上所产生的文件均在 build 目录下，build 目录已加入 .gitignore
    ```
