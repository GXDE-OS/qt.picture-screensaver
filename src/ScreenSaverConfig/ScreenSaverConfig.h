#ifndef __ScreenSaverConfig__H__
#define __ScreenSaverConfig__H__

#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QPixmap>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
class ScreenSaverConfig : public QObject
{
    Q_OBJECT
public:
    explicit ScreenSaverConfig(QObject *parent=nullptr);
    void reloadConfig();

    void setImageDirPath(QString imageDirPath);
    QString getImageDirPath();

    void setTimeout(int timeout);
    int getTimeout();

    void setOrder(bool order);
    bool getOrder();

    void reloadFilePaths();
    void loadFilePaths();

    QPixmap nextImage();
    QPixmap nextRandomImage();

    int getKeyValueInt(QString key);
    void setKeyValueInt(QString key, int val);

    QString getKeyValueString(QString key);
    void setKeyValueString(QString key, QString value);

private:
    int indexImagePath = 0;

    QSettings m_config;

    QString currentDir;
    QStringList filePaths;
    QPixmap m_default_pixmap;
};

#endif  //!__ScreenSaverConfig__H__
