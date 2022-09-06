
#include "configpanelwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <config.h>
#include <QTextStream>
#include <QDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QPropertyAnimation>
#include <QSlider>
#include <ScreenSaveImage>
#include <ScreenSaverConfig>

#include <ScreenUtils>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("图片屏保配置预览面板");

    ConfigPanelWindow window;
    window.show();

    // 移动到鼠标所在的屏幕中心
    ScreenUtils::moveCenterForCursor(window);

    // QRect firstRect = window.screen()->availableGeometry();
    // QTextStream(stdout) << "> "
    //                     << "ScreenX: " << firstRect.x() << "\n"
    //                     << "ScreenY: " << firstRect.y() << "\n"
    //                     << "ScreenWidth: " << firstRect.width() << "\n"
    //                     << "ScreenHeight: " << firstRect.height() << "\n"
    //                  q   << "CursorX: " << QCursor::pos().x() << "\n"
    //                     << "CursorY: " << QCursor::pos().y() << "\n";

    return a.exec();
}
