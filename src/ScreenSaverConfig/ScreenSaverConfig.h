#ifndef __ScreenSaverConfig__H__
#define __ScreenSaverConfig__H__

#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QPixmap>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
#include "BaseConfig"
class ScreenSaverConfig : public BaseConfig
{
    Q_OBJECT
public:
    explicit ScreenSaverConfig(QObject *parent=nullptr);
//    void reloadConfig();

    void reloadFilePaths();
    void loadFilePaths();

    QPixmap nextImage();
    QPixmap nextRandomImage();

private:
    int indexImagePath = 0;

    QString currentDir;
    QStringList filePaths;
    QPixmap m_default_pixmap;
};

#endif  //!__ScreenSaverConfig__H__
