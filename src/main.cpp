
#include <QApplication>
#include <QDesktopWidget>
#include <config.h>
#include <QTextStream>
#include <QLabel>
#include <ScreenSaverImage.h>


void moveCenter(QWidget &wm) {
    QDesktopWidget *desktop = QApplication::desktop();
    wm.move((desktop->width() - wm.width()) /2,(desktop->height() - wm.height()) /2);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);

//    ScreenSaverConfig *privateData = new ScreenSaverConfig;

    ScreenSaverImage *view = new ScreenSaverImage;
    // QWebEngineView *view = new QWebEngineView();
    
    view->setAttribute(Qt::WA_TranslucentBackground);           // 半透明的背景
    view->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 鼠标事件穿透
    // 此外将鼠标事件穿透到标准屏幕保护程序，程序收到任何移动事件后将自动还原到此前状态
    // 如果未穿透，将可用作普通程序使用，您可以用来定义为某种仅支持鼠标操作的在线资源页面

    view->setStyleSheet("background:transparent");      // 能起到某些作用
    // view->page()->setBackgroundColor(Qt::transparent);  // 能起到某些作用
 
#ifdef QT_DEBUG 
    // 预览本项目内容
    // view->page()->load(QUrl::fromLocalFile(a.applicationDirPath() + "/../resources/assets/index.html"));
    // 这是'中国台风网'页面
    // view->page()->load(QUrl("http://typhoon.nmc.cn/web.html"));
    view->setMinimumSize(QSize(650,400));
    view->show();
#else
    QDesktopWidget *desktop = QApplication::desktop();
    view->resize(desktop->width(),desktop->height());

    // 在非 Debug 模式下，视为已经打包安装版本，才设置一系列窗口标识。
    view->setWindowFlags(Qt::Tool                       // 此属性无最大最小化按键
                        |Qt::WindowStaysOnTopHint       // 窗口保持在顶部提示
                        |Qt::FramelessWindowHint        // 无框窗口提示
                        |Qt::X11BypassWindowManagerHint // 不被X11窗口管理器管理
                                                        // 一但运行，除非被 kill，将无法被控制
                                                        // 也是作为屏保正常运行时的必须属性
    );

    // 程序默认为时钟屏保，如果你想增加逼格.. 可修改此处      
    // view->page()->load(QUrl::fromLocalFile("/usr/share/" PROJECT_NAME "/assets/index.html"));
     view->show();

    // 如果你不小心手动运行了它，你将需要进入 tty 模式 kill 掉该程序
    // TODO - 这部分或许可以拯救你(实际没有)。
#endif
    moveCenter(*view);  // 移到屏幕中心
   return a.exec();
}
