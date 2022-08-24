#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <QObject>
#include <QGSettings/QGSettings>

#define GSCHEMA "com.gitee.zinface.picture-screensaver"
#define GSPATH "/com/gitee/zinface/picture-screensaver/"

#define  KEY_Path       "image-path"
#define  KEY_Timeout    "image-timeout"
#define  KEY_Visible    "tick-visible"
#define  KEY_Location   "tick-location"
#define  KEY_Color      "tick-color"
#define  KEY_ShadowDeep "tick-shadow-deep"
#define  KEY_shadowBlur "tick-shadow-blur"


class BaseConfig : public QGSettings
{
    Q_OBJECT
public:
    explicit BaseConfig(QObject *parent = nullptr);

    QString Path();
    void setPath(QString path);

    int Timeout();
    void setTimeout(int timeout);

    bool Visible();
    void setVisible(bool visible);

    QString Location();
    void setLocation(QString location);

    QString Color();
    void setColor(QString color);

    int ShadowDeep();
    void setShadowDeep(int shadowdeep);

    int shadowBlur();
    void setshadowBlur(int shadowblur);

    int LocationToIndex(QString location);
    QString LocationIndexToString(int index);

private:
    QStringList m_locations;

};

#endif // BASECONFIG_H
