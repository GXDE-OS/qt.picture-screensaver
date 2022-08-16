#include "ScreenSaverConfig.h"
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QPixmap>
#include <QDebug>
#include <QTextStream>
#include <QRandomGenerator>

ScreenSaverConfig::ScreenSaverConfig(QObject *parent) : QObject(parent)
 , m_config("picture-screensaver", "Config")
 , currentDir("")
// , indexImagePath(-1)
 , m_default_pixmap(QPixmap("://default.jpeg"))
{
    // 清除无效配置：例如目录值非空但不存在
    QString dir = getImageDirPath();
    if (!dir.isEmpty() && !QFileInfo(dir).exists()) {
        setImageDirPath("");
        qDebug() << "image 含有无效配置(已清除)\n";
    }

    if (getTimeout() < 100) {
        setTimeout(100);
    }

    currentDir = getImageDirPath();

    reloadFilePaths();
}

void ScreenSaverConfig::reloadConfig()
{
    m_config.sync();
    reloadFilePaths();
}

void ScreenSaverConfig::setImageDirPath(QString imageDirPath) {
    m_config.setValue("image/path", imageDirPath);
}
QString ScreenSaverConfig::getImageDirPath() {
    return m_config.value("image/path").toString();
}

void ScreenSaverConfig::setTimeout(int timeout) {
    m_config.setValue("image/timeout", timeout);
}
int ScreenSaverConfig::getTimeout() {
    return m_config.value("image/timeout").toInt();
}

void ScreenSaverConfig::setOrder(bool order) {
    m_config.setValue("image/order", order);
}
bool ScreenSaverConfig::getOrder() {
    return m_config.value("image/order").toBool();
}

void ScreenSaverConfig::reloadFilePaths()
{
    filePaths.clear();
    loadFilePaths();
}

void ScreenSaverConfig::loadFilePaths()
{
    QDir dir(getImageDirPath());

    QFileInfoList entrys = dir.entryInfoList();
    for (QFileInfo entry : entrys) {
        if (entry.isFile()) {
            filePaths.append(entry.filePath());
            QTextStream(stdout) << entry.filePath() << "\n";
        }

    }
}

QPixmap ScreenSaverConfig::nextImage()
{
    QPixmap pixmap = m_default_pixmap;

    // 如果没有文件的话, 不是图像将使用默认
    if (filePaths.size() == 0) {
        return pixmap;
    }

    // 如果只有一个文件的话, 不是图像将使用默认
    if (filePaths.size() == 1) {
        pixmap.load(filePaths.at(indexImagePath));
        if (pixmap.isNull()) {
            pixmap = m_default_pixmap;
        }
        return pixmap;
    }

    // 如果有多个文件的话,将尝试取下一个
    if (filePaths.size() > 1) {

        int currentIndex = indexImagePath;
        // 先扫描后面的
        for ( ;indexImagePath < filePaths.size(); ++indexImagePath) {
            pixmap.load(filePaths.at(indexImagePath));
            if (!pixmap.isNull()){
                indexImagePath++;
                goto _out;
            }
        }

        // 再扫描前面的
        for (indexImagePath = 0; indexImagePath < currentIndex ; ++indexImagePath) {
            pixmap.load(filePaths.at(indexImagePath));
            if (!pixmap.isNull()){
                indexImagePath++;
                goto _out;
            }
        }
    }

_out:
    // 最后一次确认
    if (pixmap.isNull()) {
        pixmap = m_default_pixmap;
    }
    return pixmap;;
}

QPixmap ScreenSaverConfig::nextRandomImage()
{
// 如果只有两张图怎么办: 限制5张可开始随机
    if (filePaths.size() < 5) {
        return nextImage();
    } else {
        int i = 0;
        auto glb = QRandomGenerator::global();
        do {
             i = glb->bounded(filePaths.size()-1);
             // 如果随机数已经满足
        }while(i == indexImagePath-1);
    }

    return nextImage();
}

int ScreenSaverConfig::getKeyValueInt(QString key)
{
    return m_config.value(key).toInt();
}

void ScreenSaverConfig::setKeyValueInt(QString key, int val)
{
    m_config.setValue(key, val);
}

QString ScreenSaverConfig::getKeyValueString(QString key)
{
    return m_config.value(key).toString();
}

void ScreenSaverConfig::setKeyValueString(QString key, QString value)
{
    m_config.setValue(key, value);
}
