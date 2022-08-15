
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

void moveCenter(QWidget &wm) {
    QDesktopWidget *desktop = QApplication::desktop();
    wm.move((desktop->width() - wm.width()) /2,(desktop->height() - wm.height()) /2);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("图片屏保配置预览面板");

    ConfigPanelWindow window;
    window.show();
    moveCenter(window);

    return a.exec();
}
